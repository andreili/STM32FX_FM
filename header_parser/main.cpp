#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>
#include <cstdarg>
#include <algorithm>
#include <cctype>
#include <map>

std::ifstream in_file;
std::ofstream out_file;
std::deque<std::string> in_strs;
size_t base_end;

#define FIELD_NAME_WIDTH 30
#define FIELD_BIT_NAME_WIDTH 15

std::string format(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    std::vector<char> v(1024);
    while (true)
    {
        va_list args2;
        va_copy(args2, args);
        int res = vsnprintf(v.data(), v.size(), fmt, args2);
        if ((res >= 0) && (res < static_cast<int>(v.size())))
        {
            va_end(args);
            va_end(args2);
            return std::string(v.data());
        }
        size_t size;
        if (res < 0)
            size = v.size() * 2;
        else
            size = static_cast<size_t>(res) + 1;
        v.clear();
        v.resize(size);
        va_end(args2);
    }
}

bool probe_open_file(std::string fn)
{
    /*std::regex expr("\\.h");
    if (!std::regex_match(fn, expr))
    {
        std::cout << "Invalid extention! Supported only '.h'!" << std::endl;
        return false;
    }*/
    in_file.open(fn);
    if (!in_file.is_open())
    {
        std::cout << "Unable to open file!" << std::endl;
        return false;
    }
    return true;
}

std::string removeComments(std::string prgm)
{
    int n = prgm.length();
    std::string res;

    // Flags to indicate that single line and multpile line comments
    // have started or not.
    bool s_cmt = false;
    bool m_cmt = false;


    // Traverse the given program
    for (int i=0; i<n; i++)
    {
        // If single line comment flag is on, then check for end of it
        if (s_cmt == true && prgm[i] == '\n')
            s_cmt = false;

        // If multiple line comment is on, then check for end of it
        else if  (m_cmt == true && prgm[i] == '*' && prgm[i+1] == '/')
            m_cmt = false,  i++;

        // If this character is in a comment, ignore it
        else if (s_cmt || m_cmt)
            continue;

        // Check for beginning of comments and set the approproate flags
        else if (prgm[i] == '/' && prgm[i+1] == '/')
            s_cmt = true, i++;
        else if (prgm[i] == '/' && prgm[i+1] == '*')
            m_cmt = true,  i++;

        // If current character is a non-comment character, append it to res
        else  res += prgm[i];
    }
    return res;
}

void prepare_input()
{
    std::string buf;
    while (!in_file.eof())
    {
        std::string tmp;
        std::getline(in_file, tmp);
        tmp += '\n';
        buf += tmp;
    }
    buf = removeComments(buf);
    std::istringstream tokenStream(buf);
    std::string token;
    while (std::getline(tokenStream, token, '\n'))
        in_strs.push_back(token);
}

enum class EStage
{
    IFNDEF,
    CORE_DEF,
    IRQs,
    INCLUDES,
    REGS,
    BASES,
    TYPEDEFS,
    FIELDS,
    DEF_IS,
    CONSTS,
    END,
};

typedef struct
{
    std::string name;
    std::string value;
} define_t;

typedef struct
{
    std::string name;
    std::string reg_name;
    std::string offset;
} REG_BASE_t;

typedef struct
{
    std::string name;
    std::string mask;
    int         pos;
    int         bits;
    int         array_index;
} REG_FIELD_MASKS_t;

typedef struct
{
    std::string type;
    std::string name;
    std::string array_size;
    std::string synonym;
    std::deque<REG_FIELD_MASKS_t> masks;
} REG_FIELD_t;

typedef std::deque<REG_FIELD_t> fields_t;

typedef struct
{
    std::string name;
    std::string sub_name;
    std::deque<std::string> base_num;
    std::deque<std::string> synonyms;
    std::deque<REG_FIELD_t> fields;
    std::deque<REG_FIELD_MASKS_t> masks;
} REG_t;

typedef struct
{
    std::string bits;
    std::string chip;
    std::deque<define_t> core_defs;
    std::deque<define_t> IRQs;
    std::deque<std::string> includes;
    std::deque<REG_BASE_t> bases;
    std::deque<std::string> regs_defs;
    std::deque<REG_t> regs;
    std::deque<define_t> consts;
} STM_t;

STM_t stm;

std::string to_upper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::toupper(c); });
    return s;
}

bool is_REG(REG_t& reg, std::string name)
{
    name = to_upper(name);
    if (reg.sub_name.size())
    {
        if (to_upper(reg.sub_name).compare(name) == 0)
            return true;
    }
    else
    {
        if (to_upper(reg.name).compare(name) == 0)
            return true;
    }
    for (std::string& syn : reg.synonyms)
    {
        if (to_upper(syn).compare(name) == 0)
            return true;
    }
    return false;
}

bool parse_header(std::string& str)
{
    static std::smatch smatch;
    static std::regex reg("#define __STM(\\d+)F(\\d+)xx_H");
    if (std::regex_search(str, smatch, reg))
    {
        stm.bits = smatch[1];
        stm.chip = smatch[2];
        return true;
    }
    else
        return false;
}

bool parse_core_defs(std::string& str)
{
    static std::smatch smatch;
    static std::regex reg("#define (__\\S+) +(\\S+)");
    if (std::regex_search(str, smatch, reg))
    {
        define_t def;
        def.name = smatch[1];
        def.value = smatch[2];
        stm.core_defs.push_back(def);
    }
    else if (str.find("typedef enum") != std::string::npos)
        return true;
    return false;
}

bool parse_IRQs(std::string& str)
{
    static std::smatch smatch;
    if (str.find("} IRQn_Type;") != std::string::npos)
        return true;
    else
    {
        static std::regex expr("(\\S+)_IRQn\\s*=\\s*(\\-*\\d+)");
        if (std::regex_search(str, smatch, expr))
        {
            define_t def;
            def.name = smatch[1];
            def.value = smatch[2];
            stm.IRQs.push_back(def);
        }
    }
    return false;
}

bool parse_includes(std::string& str)
{
    static std::smatch smatch;
    if (str.find("typedef struct") != std::string::npos)
        return true;
    else
    {
        static std::regex expr("#include\\s*[\"<](\\S+).h[\">]");
        if (std::regex_search(str, smatch, expr))
            stm.includes.push_back(smatch[1]);
    }
    return false;
}

bool parse_regs(std::string& str, REG_t& reg)
{
    static std::regex expr("}\\s*([A-Z\\d_]+)_([A-Za-z_\\d]*)(_*)TypeDef;");
    static std::regex expr_f("\\s+(\\S+\\s?\\S+\\s?[const]?\\S+)\\s+([A-Za-z\\d]+)([\\[\\]\\dxA-Z]*);");
    static std::smatch smatch;
    if (std::regex_search(str, smatch, expr))
    {
        reg.name = smatch[1];
        std::string name_ex = smatch[2];
        if (name_ex[name_ex.size() - 1] == '_')
            name_ex.erase(name_ex.size() - 1);
        if (name_ex.size())
            reg.sub_name = reg.name + "_" + name_ex;
        std::cout << reg.name << ":" << reg.sub_name << std::endl;
        stm.regs.push_back(reg);
        reg.base_num.clear();
        reg.masks.clear();
        reg.fields.clear();
        reg.synonyms.clear();
        reg.sub_name = "";
    }
    else if (std::regex_search(str, smatch, expr_f))
    {
        REG_FIELD_t field;
        field.type = smatch[1];
        field.name = smatch[2];
        field.synonym = "";
        field.array_size = "";
        if (smatch[3].matched)
            field.array_size = smatch[3];
        reg.fields.push_back(field);
    }
    else if (str.find("#define") != std::string::npos)
        return true;
    return false;
}

typedef struct
{
    std::string reg_name;
    std::string struct_name;
} rsyn_t;

std::vector<rsyn_t> reg_syns {
    {"TIM1",     "TIM"},
    {"TIM2",     "TIM"},
    {"TIM3",     "TIM"},
    {"TIM4",     "TIM"},
    {"TIM5",     "TIM"},
    {"TIM6",     "TIM"},
    {"TIM7",     "TIM"},
    {"TIM8",     "TIM"},
    {"TIM9",     "TIM"},
    {"TIM10",    "TIM"},
    {"TIM11",    "TIM"},
    {"TIM12",    "TIM"},
    {"TIM13",    "TIM"},
    {"TIM14",    "TIM"},
    {"TIM15",    "TIM"},
    {"TIM16",    "TIM"},
    {"SPI1",     "SPI"},
    {"SPI2",     "SPI"},
    {"SPI3",     "SPI"},
    {"SPI4",     "SPI"},
    {"SPI5",     "SPI"},
    {"SPI6",     "SPI"},
    {"ADC1",     "ADC"},
    {"ADC2",     "ADC"},
    {"ADC3",     "ADC"},
    {"CAN1",     "CAN"},
    {"CAN2",     "CAN"},
    {"CAN3",     "CAN"},
    {"I2C1",     "I2C"},
    {"I2C2",     "I2C"},
    {"I2C3",     "I2C"},
    {"I2C4",     "I2C"},
    {"I2C5",     "I2C"},
    {"I2C6",     "I2C"},
    {"I2S1",     "I2S"},
    {"I2S2",     "I2S"},
    {"I2S3",     "I2S"},
    {"I2S4",     "I2S"},
    {"I2S5",     "I2S"},
    {"I2S1",     "I2S"},
    {"USART1",   "USART"},
    {"USART2",   "USART"},
    {"USART3",   "USART"},
    {"UART4",    "USART"},
    {"UART5",    "USART"},
    {"USART6",   "USART"},
    {"USART7",   "USART"},
    {"USART8",   "USART"},
    {"USART9",   "USART"},
    {"DMA1_Stream0", "DMA_Stream"},
    {"DMA1_Stream1", "DMA_Stream"},
    {"DMA1_Stream2", "DMA_Stream"},
    {"DMA1_Stream3", "DMA_Stream"},
    {"DMA1_Stream4", "DMA_Stream"},
    {"DMA1_Stream5", "DMA_Stream"},
    {"DMA1_Stream6", "DMA_Stream"},
    {"DMA1_Stream7", "DMA_Stream"},
    {"DMA2_Stream0", "DMA_Stream"},
    {"DMA2_Stream1", "DMA_Stream"},
    {"DMA2_Stream2", "DMA_Stream"},
    {"DMA2_Stream3", "DMA_Stream"},
    {"DMA2_Stream4", "DMA_Stream"},
    {"DMA2_Stream5", "DMA_Stream"},
    {"DMA2_Stream6", "DMA_Stream"},
    {"DMA2_Stream7", "DMA_Stream"},
    {"DMA1",    "DMA"},
    {"DMA2",    "DMA"},
    {"GPIOA",   "GPIO"},
    {"GPIOB",   "GPIO"},
    {"GPIOC",   "GPIO"},
    {"GPIOD",   "GPIO"},
    {"GPIOE",   "GPIO"},
    {"GPIOF",   "GPIO"},
    {"GPIOG",   "GPIO"},
    {"GPIOH",   "GPIO"},
    {"GPIOI",   "GPIO"},
};

bool parse_BASEs(std::string& str)
{
    static std::regex expr("#define (\\S+)(_BASE|_END|_SIZE)\\s+(\\S+)(\\ \\+\\ \\S+)?");
    static std::regex expr_syn("#define (\\S+)_BASE\\s+(\\S+)_BASE$");
    static std::smatch smatch;
    if (std::regex_search(str, smatch, expr))
    {
        REG_BASE_t base;
        base.reg_name = smatch[1];
        base.name = base.reg_name + smatch[2].str();
        base.offset = smatch[3];
        if (smatch[4].matched)
            base.offset += smatch[4];
        if (smatch[2].compare("_BASE") == 0)
        {
            for (rsyn_t &rsyn : reg_syns)
                if (base.reg_name.compare(rsyn.reg_name) == 0)
                {
                    for (REG_t& reg : stm.regs)
                        if (is_REG(reg, rsyn.struct_name))
                        {
                            reg.base_num.push_back(rsyn.reg_name);
                            std::cout << rsyn.reg_name << "=" << reg.name << ":" << reg.sub_name << "=" << reg.base_num.size() << std::endl;
                            break;
                        }
                    break;
                }
        }

        stm.bases.push_back(base);
        if (std::regex_search(str, smatch, expr_syn))
        {
            std::string reg_name = smatch[2];
            for (REG_t& reg : stm.regs)
                if (is_REG(reg, reg_name))
                {
                    reg.synonyms.push_back(smatch[1]);
                    break;
                }
        }
    }
    else if (str.find("_Pos") != std::string::npos)
        return true;
    return false;
}

typedef struct
{
    std::string src_reg_name;
    std::string name;
    std::string field_name;
    std::string reg_name;
    int         index;
    int         array_index;
} syn_t;

std::vector<syn_t> field_syns {
    {"ADC",     "CSR",    "CSR",     "ADC123_Common", 0, -1},
    {"CAN",     "TI0R",   "TIR",     "CAN_TxMailBox", 0, -1},
    {"CAN",     "TDT0R",  "TDTR",    "CAN_TxMailBox", 0, -1},
    {"CAN",     "TDL0R",  "TDLR",    "CAN_TxMailBox", 0, -1},
    {"CAN",     "TDH0R",  "TDHR",    "CAN_TxMailBox", 0, -1},
    {"CAN",     "TI1R",   "TIR",     "CAN_TxMailBox", 1, -1},
    {"CAN",     "TDT1R",  "TDTR",    "CAN_TxMailBox", 1, -1},
    {"CAN",     "TDL1R",  "TDLR",    "CAN_TxMailBox", 1, -1},
    {"CAN",     "TDH1R",  "TDHR",    "CAN_TxMailBox", 1, -1},
    {"CAN",     "TI2R",   "TIR",     "CAN_TxMailBox", 2, -1},
    {"CAN",     "TDT2R",  "TDTR",    "CAN_TxMailBox", 2, -1},
    {"CAN",     "TDL2R",  "TDLR",    "CAN_TxMailBox", 2, -1},
    {"CAN",     "TDH2R",  "TDHR",    "CAN_TxMailBox", 2, -1},
    {"CAN",     "RI0R",   "RIR",     "CAN_FIFOMailBox", 0, -1},
    {"CAN",     "RDT0R",  "RDTR",    "CAN_FIFOMailBox", 0, -1},
    {"CAN",     "RDL0R",  "RDLR",    "CAN_FIFOMailBox", 0, -1},
    {"CAN",     "RDH0R",  "RDHR",    "CAN_FIFOMailBox", 0, -1},
    {"CAN",     "RI1R",   "RIR",     "CAN_FIFOMailBox", 1, -1},
    {"CAN",     "RDT1R",  "RDTR",    "CAN_FIFOMailBox", 1, -1},
    {"CAN",     "RDL1R",  "RDLR",    "CAN_FIFOMailBox", 1, -1},
    {"CAN",     "RDH1R",  "RDHR",    "CAN_FIFOMailBox", 1, -1},
    {"CAN",     "RI2R",   "RIR",     "CAN_FIFOMailBox", 2, -1},
    {"CAN",     "RDT2R",  "RDTR",    "CAN_FIFOMailBox", 2, -1},
    {"CAN",     "RDL2R",  "RDLR",    "CAN_FIFOMailBox", 2, -1},
    {"CAN",     "RDH2R",  "RDHR",    "CAN_FIFOMailBox", 2, -1},
    {"CAN",     "F0R1",   "FR1",     "CAN_FilterRegister", 0, -1},
    {"CAN",     "F0R2",   "FR2",     "CAN_FilterRegister", 0, -1},
    {"CAN",     "F1R1",   "FR1",     "CAN_FilterRegister", 1, -1},
    {"CAN",     "F1R2",   "FR2",     "CAN_FilterRegister", 1, -1},
    {"CAN",     "F2R1",   "FR1",     "CAN_FilterRegister", 2, -1},
    {"CAN",     "F2R2",   "FR2",     "CAN_FilterRegister", 2, -1},
    {"CAN",     "F3R1",   "FR1",     "CAN_FilterRegister", 3, -1},
    {"CAN",     "F3R2",   "FR2",     "CAN_FilterRegister", 3, -1},
    {"CAN",     "F4R1",   "FR1",     "CAN_FilterRegister", 4, -1},
    {"CAN",     "F4R2",   "FR2",     "CAN_FilterRegister", 4, -1},
    {"CAN",     "F5R1",   "FR1",     "CAN_FilterRegister", 5, -1},
    {"CAN",     "F5R2",   "FR2",     "CAN_FilterRegister", 5, -1},
    {"CAN",     "F6R1",   "FR1",     "CAN_FilterRegister", 6, -1},
    {"CAN",     "F6R2",   "FR2",     "CAN_FilterRegister", 6, -1},
    {"CAN",     "F7R1",   "FR1",     "CAN_FilterRegister", 7, -1},
    {"CAN",     "F7R2",   "FR2",     "CAN_FilterRegister", 7, -1},
    {"CAN",     "F8R1",   "FR1",     "CAN_FilterRegister", 8, -1},
    {"CAN",     "F8R2",   "FR2",     "CAN_FilterRegister", 8, -1},
    {"CAN",     "F9R1",   "FR1",     "CAN_FilterRegister", 9, -1},
    {"CAN",     "F9R2",   "FR2",     "CAN_FilterRegister", 9, -1},
    {"CAN",     "F10R1",  "FR1",     "CAN_FilterRegister", 10, -1},
    {"CAN",     "F10R2",  "FR2",     "CAN_FilterRegister", 10, -1},
    {"CAN",     "F11R1",  "FR1",     "CAN_FilterRegister", 11, -1},
    {"CAN",     "F11R2",  "FR2",     "CAN_FilterRegister", 11, -1},
    {"CAN",     "F12R1",  "FR1",     "CAN_FilterRegister", 12, -1},
    {"CAN",     "F12R2",  "FR2",     "CAN_FilterRegister", 12, -1},
    {"CAN",     "F13R1",  "FR1",     "CAN_FilterRegister", 13, -1},
    {"CAN",     "F13R2",  "FR2",     "CAN_FilterRegister", 13, -1},
    {"DCMI",    "CWSTRT", "CWSTRTR", "DCMI", 0, -1},
    {"DCMI",    "CWSIZE", "CWSIZER", "DCMI", 0, -1},
    {"DMA",     "SxCR",   "CR",      "DMA_Stream", 0, -1},
    {"DMA",     "SxNDT",  "NDTR",    "DMA_Stream", 0, -1},
    {"DMA",     "SxPAR",  "PAR",     "DMA_Stream", 0, -1},
    {"DMA",     "SxM0AR", "M0AR",    "DMA_Stream", 0, -1},
    {"DMA",     "SxM1AR", "M1AR",    "DMA_Stream", 0, -1},
    {"DMA",     "SxFCR",  "FCR",     "DMA_Stream", 0, -1},
    {"FSMC",    "BCR1",   "BTCR",    "FSMC_Bank1", 0, 0},
    {"FSMC",    "BTR1",   "BTCR",    "FSMC_Bank1", 0, 1},
    {"FSMC",    "BCR2",   "BTCR",    "FSMC_Bank1", 0, 2},
    {"FSMC",    "BTR2",   "BTCR",    "FSMC_Bank1", 0, 3},
    {"FSMC",    "BCR3",   "BTCR",    "FSMC_Bank1", 0, 4},
    {"FSMC",    "BTR3",   "BTCR",    "FSMC_Bank1", 0, 5},
    {"FSMC",    "BCR4",   "BTCR",    "FSMC_Bank1", 0, 6},
    {"FSMC",    "BTR4",   "BTCR",    "FSMC_Bank1", 0, 7},
    {"FSMC",    "BWTR1",  "BWTR",    "FSMC_Bank1E", 0, 0},
    {"FSMC",    "BWTR2",  "BWTR",    "FSMC_Bank1E", 0, 1},
    {"FSMC",    "BWTR3",  "BWTR",    "FSMC_Bank1E", 0, 2},
    {"FSMC",    "BWTR4",  "BWTR",    "FSMC_Bank1E", 0, 3},
    {"FSMC",    "PCR2",   "PCR2",    "FSMC_Bank2_3", 0, -1},
    {"FSMC",    "SR2",    "SR2",     "FSMC_Bank2_3", 0, -1},
    {"FSMC",    "PMEM2",  "PMEM2",   "FSMC_Bank2_3", 0, -1},
    {"FSMC",    "PATT2",  "PATT2",   "FSMC_Bank2_3", 0, -1},
    {"FSMC",    "ECCR2",  "ECCR2",   "FSMC_Bank2_3", 0, -1},
    {"FSMC",    "PCR3",   "PCR3",    "FSMC_Bank2_3", 0, -1},
    {"FSMC",    "SR3",    "SR3",     "FSMC_Bank2_3", 0, -1},
    {"FSMC",    "PMEM3",  "PMEM3",   "FSMC_Bank2_3", 0, -1},
    {"FSMC",    "PATT3",  "PATT3",   "FSMC_Bank2_3", 0, -1},
    {"FSMC",    "ECCR3",  "ECCR3",   "FSMC_Bank2_3", 0, -1},
    {"FSMC",    "PCR4",   "PCR4",    "FSMC_Bank4", 0, -1},
    {"FSMC",    "SR4",    "SR4",     "FSMC_Bank4", 0, -1},
    {"FSMC",    "PMEM4",  "PMEM4",   "FSMC_Bank4", 0, -1},
    {"FSMC",    "PATT4",  "PATT4",   "FSMC_Bank4", 0, -1},
    {"FSMC",    "PIO4",   "PIO4",    "FSMC_Bank4", 0, -1},
    {"GPIO",    "AFRL",   "AFR",     "GPIO", 0, 0},
    {"GPIO",    "AFRH",   "AFR",     "GPIO", 0, 1},
    {"GPIO",    "BRR",    "BSRR",    "GPIO", 0, -1},
    {"SDIO",    "RESP0",  "RESPCMD", "SDIO", 0, -1},
    {"SYSCFG",  "EXTICR1","EXTICR",  "SYSCFG", 0, 0},
    {"SYSCFG",  "EXTICR2","EXTICR",  "SYSCFG", 0, 1},
    {"SYSCFG",  "EXTICR3","EXTICR",  "SYSCFG", 0, 2},
    {"SYSCFG",  "EXTICR4","EXTICR",  "SYSCFG", 0, 3},
    {"DBGMCU",  "APB1",   "APB1FZ",  "DBGMCU", 0, -1},
    {"DBGMCU",  "APB2",   "APB2FZ",  "DBGMCU", 0, -1},
    {"USB_OTG", "GOTGCTL","GOTGCTL", "USB_OTG_Global", 0, -1},
    {"USB_OTG", "GOTGINT","GOTGINT", "USB_OTG_Global", 0, -1},
    {"USB_OTG", "GAHBCFG","GAHBCFG", "USB_OTG_Global", 0, -1},
    {"USB_OTG", "GUSBCFG","GUSBCFG", "USB_OTG_Global", 0, -1},
    {"USB_OTG", "GINTSTS","GINTSTS", "USB_OTG_Global", 0, -1},
    {"USB_OTG", "GINTMSK","GINTMSK", "USB_OTG_Global", 0, -1},
    {"USB_OTG", "GRXSTSR","GRXSTSR", "USB_OTG_Global", 0, -1},
    {"USB_OTG", "GRXSTSP","GRXSTSP", "USB_OTG_Global", 0, -1},
    {"USB_OTG", "GRXFSIZ","GRXFSIZ", "USB_OTG_Global", 0, -1},
    {"USB_OTG", "DIEPTXF0_HNPTXFSIZ","DIEPTXF0_HNPTXFSIZ", "USB_OTG_Global", 0, -1},
    {"USB_OTG", "HNPTXSTS","HNPTXSTS", "USB_OTG_Global", 0, -1},
    {"USB_OTG", "GCCFG",  "GCCFG",   "USB_OTG_Global", 0, -1},
    {"USB_OTG", "CID",    "CID",     "USB_OTG_Global", 0, -1},
    {"USB_OTG", "HPTXFSIZ","HPTXFSIZ", "USB_OTG_Global", 0, -1},
    {"USB_OTG", "DIEPTXF", "DIEPTXF", "USB_OTG_Global", 0, -1},
    {"USB_OTG", "HCFG",   "HCFG",    "USB_OTG_Host", 0, -1},
    {"USB_OTG", "DCFG",   "DCFG",    "USB_OTG_Device", 0, -1},
};

REG_FIELD_t* get_field(REG_t& reg, std::string name, std::string fsyn)
{
    for (REG_FIELD_t& field : reg.fields)
        if ((field.name.compare(name) == 0) ||
            (field.synonym.compare(name) == 0) ||
            (fsyn.size() && (field.name.compare(fsyn) == 0)) ||
            (fsyn.size() && (field.synonym.compare(fsyn) == 0)))
            return &field;
    return nullptr;
}

REG_FIELD_MASKS_t* get_field_bits(std::string reg_name, std::string field_name, std::string bits_name)
{
    std::string fsyn;
    std::string rfsyn;
    int idx = -1;
    int array_index = -1;
    for (syn_t& syn : field_syns)
        if ((syn.name.compare(field_name) == 0) &&
            (reg_name.compare(syn.src_reg_name) == 0))
        {
            fsyn = syn.field_name;
            rfsyn = syn.reg_name;
            idx = syn.index;
            array_index = syn.array_index;
        }
    if (idx > -1)
        reg_name = rfsyn;
    if (bits_name.size() == 0)
        bits_name = "DATA";
    for (REG_t& reg : stm.regs)
        if (is_REG(reg, reg_name))
        {
            REG_FIELD_t* field = get_field(reg, field_name, fsyn);
            if (field != nullptr)
            {
                for (REG_FIELD_MASKS_t& mask : field->masks)
                    if (mask.name.compare(bits_name) == 0)
                        return &mask;
                REG_FIELD_MASKS_t mask;
                mask.name = bits_name;
                mask.array_index = array_index;
                field->masks.push_back(mask);
                return &field->masks[field->masks.size() - 1];
            }
        }
    return nullptr;
}

REG_FIELD_t* get_field(std::string reg_name, std::string field_name)
{
    for (REG_t& reg : stm.regs)
        if (is_REG(reg, reg_name))
            for (REG_FIELD_t& field : reg.fields)
            {
                if ((field.name.compare(field_name) == 0) ||
                    (field.synonym.compare(field_name) == 0))
                    return &field;
            }
    return nullptr;
}

bool parse_sync(std::string& str)
{
    static std::regex expr_syn("#define\\s+([A-Z\\d]+)_([A-Za-z\\d]+)_([\\S\\d]+)\\s+([A-Z\\d]+)_([A-Z\\d]+)_([A-Za-z\\d_]+)(?!_Msk)");
    static std::regex expr_nsyn("#define\\s+([A-Z\\d]+)_([A-Za-z\\d]+)_([\\S\\d]+)\\s+([A-Z\\d]+)_([A-Z\\d]+)_([A-Za-z\\d_]+)(_Msk)");
    static std::smatch smatch, smatch1;
    if (std::regex_search(str, smatch, expr_syn))
    {
        //std::cout << "-" << std::endl;
        if (std::regex_search(str, smatch1, expr_nsyn))
            return false;
        REG_FIELD_t* field = get_field(smatch[1], smatch[2]);
        std::string syn = smatch[5];
        if (field == nullptr)
        {
            field = get_field(smatch[4], smatch[5]);
            syn = smatch[2];
            if (field == nullptr)
            {
                return false;
                //std::exit(1);
            }
        }
        if ((field->name.compare(syn) != 0) &&
            (field->synonym.compare(syn) != 0))
            field->synonym = syn;
    }
    else if (str.find("#define IS_") != std::string::npos)
        return true;
    return false;
}

bool parse_fields(std::string& str)
{
    static std::regex expr_pos("#define\\s+(USB_OTG|[A-Z\\d]+)_([A-Za-z\\d]+)_*([\\S\\d]*)_Pos\\s+\\(([\\S\\d]+)U\\)");
    static std::regex expr_msk("#define\\s+(USB_OTG|[A-Z\\d]+)_([A-Za-z\\d]+)_*([\\S\\d]*)_Msk\\s+\\(0x([\\S\\d]+)U\\s+<<");
    static std::regex expr_syn("#define\\s+(USB_OTG|[A-Z\\d]+)_([A-Za-z\\d]+)_*([\\S\\d]*)\\s+([A-Z\\d]+)_([A-Z\\d]+)_([A-Za-z\\d_]+)(?!_Msk)");
    static std::regex expr_def("#define\\s+([A-Za-z\\d_]+)_SUPPORT");
    static std::regex expr_skip_redef("#define \\S+_\\d+\\s+");
    static std::regex expr_skip_name("#define (\\S+)\\s+\\1_Msk");
    static std::smatch smatch;
    if (std::regex_search(str, smatch, expr_pos))
    {
        if (smatch[1].compare("USB_OTG") == 0)
            return false;
        // field position
        REG_FIELD_MASKS_t* mask = get_field_bits(smatch[1], smatch[2], smatch[3]);
        if (mask == nullptr)
        {
            std::cout << str << std::endl;
            std::exit(1);
        }
        mask->pos = std::stoi(smatch[4]);
    }
    else if (std::regex_search(str, smatch, expr_msk))
    {
        if (smatch[1].compare("USB_OTG") == 0)
            return false;
        // field width
        REG_FIELD_MASKS_t* mask = get_field_bits(smatch[1], smatch[2], smatch[3]);
        if (mask == nullptr)
        {
            std::cout << str << std::endl;
            std::exit(1);
        }
        mask->mask = smatch[4];
        int pos = 0;
        int width = 0;
        while (mask->mask[pos])
        {
            char bit_mask = mask->mask[pos++];
            int bits = ((bit_mask >= 'A') ? (bit_mask - 'A' + 10) : (bit_mask - '0'));
            int num = 0;
            while ((bits & 0x01) == 0x01)
            {
                ++num;
                bits >>= 1;
            }
            width = width + num;
        }
        mask->bits = width;
    }
    else if (std::regex_search(str, smatch, expr_syn))
    {
        /*std::cout << "-" << std::endl;
        REG_FIELD_t* field = get_field(smatch[1], smatch[5]);
        if (field == nullptr)
        {
            std::cout << str << std::endl << "\t" << smatch[1] << "." << smatch[2] << std::endl;
            std::exit(1);
        }
        field->synonym = smatch[2];*/
    }
    else if (std::regex_search(str, smatch, expr_def))
    {
        stm.regs_defs.push_back(smatch[1]);
    }
    else if (std::regex_search(str, smatch, expr_skip_redef))
    {}
    else if (std::regex_search(str, smatch, expr_skip_name))
    {}
    else if (str.find("#define IS_") != std::string::npos)
        return true;
    else if (str.size())
        std::cout << str << std::endl;
    return false;
}

bool parse_consts(std::string& str)
{
    static std::smatch smatch;
    static std::regex reg("#define (__\\S+) +(\\S+)");
    if (std::regex_search(str, smatch, reg))
    {
        define_t def;
        def.name = smatch[1];
        def.value = smatch[2];
        stm.consts.push_back(def);
    }
    else if (str.find("__cplusplus") != std::string::npos)
        return true;
    return false;
}

void write_header()
{
    out_file << "#ifndef __STM" << stm.bits << "F" << stm.chip << "xx_H_" << std::endl;
    out_file << "#define __STM" << stm.bits << "F" << stm.chip << "xx_H_" << std::endl;
    out_file << std::endl;
    out_file << "#include <stdint.h>" << std::endl;
    out_file << std::endl;
    out_file << "template <std::uint32_t... bitmask>" << std::endl;
    out_file << "inline constexpr std::uint32_t SetBits()" << std::endl;
    out_file << "{" << std::endl;
    out_file << "    return (bitmask | ...);" << std::endl;
    out_file << "}" << std::endl;
    out_file << std::endl;
}

void write_defines()
{
    for (define_t& def : stm.core_defs)
        out_file << "#define " << std::setw(FIELD_NAME_WIDTH) << std::left << def.name << def.value << std::endl;
    out_file << std::endl;
}

void write_IRQs()
{
    out_file << "namespace STM" << stm.bits << "_REGS" << std::endl;
    out_file << "{" << std::endl;
    out_file << "    enum class IRQn: std::int32_t" << std::endl;
    out_file << "    {" << std::endl;
    for (define_t &irq : stm.IRQs)
        out_file << "        " << std::setw(FIELD_NAME_WIDTH) << std::left << irq.name << " = " << irq.value << "," << std::endl;
    out_file << "    };" << std::endl;
    out_file << "}" << std::endl;
    out_file << std::endl;
    out_file << "//namespace ARM = STM" << stm.bits << ";" << std::endl;
    out_file << std::endl;
    out_file << "#ifdef __cplusplus" << std::endl;
    out_file << "  #define   __I     volatile             /*!< Defines 'read only' permissions */" << std::endl;
    out_file << "#else" << std::endl;
    out_file << "  #define   __I     volatile const       /*!< Defines 'read only' permissions */" << std::endl;
    out_file << "#endif" << std::endl;
    out_file << "#define     __O     volatile             /*!< Defines 'write only' permissions */" << std::endl;
    out_file << "#define     __IO    volatile             /*!< Defines 'read / write' permissions */" << std::endl;
    out_file << "" << std::endl;
    out_file << "/* following defines should be used for structure members */" << std::endl;
    out_file << "#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */" << std::endl;
    out_file << "#define     __OM     volatile            /*! Defines 'write only' structure member permissions */" << std::endl;
    out_file << "#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */" << std::endl;
    out_file << std::endl;
    for (std::string& inc : stm.includes)
        out_file << "//#include \"" << inc << ".hpp\"" << std::endl;
    out_file << std::endl;
    out_file << "//namespace CORTEX = CM" << stm.chip[0] << ";" << std::endl;
    out_file << std::endl;
}

void write_BASEs()
{
    out_file << "namespace STM" << stm.bits << std::endl;
    out_file << "{" << std::endl;
    for (REG_BASE_t &base : stm.bases)
        out_file << "    static constexpr std::uint32_t "<< std::setw(FIELD_NAME_WIDTH) << std::left <<
                    to_upper(base.name) << " = " << base.offset << ";" << std::endl;
    out_file << "}" << std::endl;
    out_file << std::endl;
    for (REG_BASE_t &base : stm.bases)
        out_file << "#define __" << base.reg_name << " 1" << std::endl;
    out_file << std::endl;
}

bool write_field_bits(REG_FIELD_t& field)
{
    bool has_bit_fileds = false;
    out_file << "            union " << field.name << "_t" << std::endl;
    out_file << "            {" << std::endl;
    out_file << "                struct" << std::endl;
    out_file << "                {" << std::endl;
    int idx = 0;
    for (REG_FIELD_MASKS_t& mask : field.masks)
    {
        int res = 0;
        while (idx < mask.pos)
        {
            ++res;
            ++idx;
        }
        if (res)
        {
            out_file << "                    uint32_t " << std::setw(FIELD_BIT_NAME_WIDTH) << std::left << ("reserved" + std::to_string(idx - res)) <<
                        ": " << res << ";" << std::endl;
        }
        out_file << "                    uint32_t " << std::setw(FIELD_BIT_NAME_WIDTH) << std::left << mask.name << ": " << mask.bits << ";" << std::endl;
        idx += mask.bits;
        if (mask.bits == 1)
            has_bit_fileds = true;
    }
    if (idx < 32)
        out_file << "                    uint32_t " << std::setw(FIELD_BIT_NAME_WIDTH) << std::left << ("reserved" + std::to_string(idx)) <<
                    ": " << (32 - idx) << ";" << std::endl;
    out_file << "                };" << std::endl;
    out_file << "                uint32_t RAW;" << std::endl;
    out_file << "            };" << std::endl;
    return has_bit_fileds;
}

void write_field_enum(REG_FIELD_t& field)
{
    if (field.masks.size())
    {
        out_file << "            enum class EMasks: uint32_t" << std::endl;
        out_file << "            {" << std::endl;
        for (REG_FIELD_MASKS_t& mask : field.masks)
            out_file << "                "<< std::setw(FIELD_NAME_WIDTH - 8) << std::left << mask.name << " = (0x" << mask.mask << "U << " <<
                        mask.pos << ")," << std::endl;
        out_file << "            };" << std::endl;
    }
}

void write_field_flags_operators(bool is_RO, std:: string type_name, std::string base, std::string fname, bool multiple_regs)
{
    if (!is_RO)
    {
        out_file << "            template <EMasks ... flags>" << std::endl;
        if (multiple_regs)
            out_file << "            static inline void set_flags(uint32_t base)" << std::endl;
        else
            out_file << "            static inline void set_flags()" << std::endl;
        out_file << "            {" << std::endl;
        out_file << "                reinterpret_cast<" + type_name + "_t*>(" << base << ")->" + fname +  " |= SetBits<(std::uint32_t)flags...>();" << std::endl;
        out_file << "            }" << std::endl;
        out_file << "            template <EMasks ... flags>" << std::endl;
        if (multiple_regs)
            out_file << "            static inline void clear_flags(uint32_t base)" << std::endl;
        else
            out_file << "            static inline void clear_flags()" << std::endl;
        out_file << "            {" << std::endl;
        out_file << "                reinterpret_cast<" + type_name + "_t*>(" << base << ")->" + fname + " &= ~(SetBits<(std::uint32_t)flags...>());" << std::endl;
        out_file << "            }" << std::endl;
    }
    out_file << "            template <EMasks ... flags>" << std::endl;
    if (multiple_regs)
        out_file << "            static inline bool get_flags(uint32_t base)" << std::endl;
    else
        out_file << "            static inline bool get_flags()" << std::endl;
    out_file << "            {" << std::endl;
    out_file << "                return (reinterpret_cast<" + type_name + "_t*>(" << base << ")->" + fname + " & SetBits<(std::uint32_t)flags...>());" << std::endl;
    out_file << "            }" << std::endl;
}

void wfite_field_accs(REG_FIELD_t& field, std::string base, std::string name, bool has_bit_fileds, bool multiple_regs)
{
    bool indexed = (field.array_size.size() > 0);
    std::string index_hdr = "";
    std::string index_hdr_ex = "";
    std::string index = "";
    std::string fname = field.name;
    if (indexed)
    {
        index_hdr = "uint32_t idx";
        index_hdr_ex = "uint32_t idx, ";
        index = "[idx]";
        std::regex ex_idx("(\\S+)\\[");
        std::smatch smatch;
        if (std::regex_search(fname, smatch, ex_idx))
            fname = smatch[1];
    }

    if (multiple_regs)
    {
        base = "base";
        if (index_hdr.size())
            index_hdr = "uint32_t base, " + index_hdr;
        else
            index_hdr = "uint32_t base";
        index_hdr_ex = "uint32_t base, " + index_hdr_ex;
    }

    std::regex ex_const("(const\\s)");
    std::smatch smatch;

    // field definition (legacy support)
    for (REG_FIELD_MASKS_t& mask : field.masks)
    {
        std::string ff = name + "_" + fname + "_" + mask.name;
        out_file << "            #define __" << std::setw(FIELD_NAME_WIDTH - 8) << std::left << ff << " (0x" << mask.mask << "U << " <<
                    mask.pos << ")" << std::endl;
    }

    std::string io_mode = "";
    if (field.type.find("const ") != std::string::npos)
        io_mode = "__IO const ";
    else if (field.type.find("__IO") != std::string::npos)
        io_mode = "__IO ";
    else if (field.type.find("__I") != std::string::npos)
        io_mode = "__I ";
    else if (field.type.find("__O") != std::string::npos)
        io_mode = "__O ";

    bool is_RO = std::regex_search(field.type, smatch, ex_const);
    out_file << "            static inline uint32_t get(" << index_hdr << ") { return reinterpret_cast<" <<
                name << "_t*>(" << base << ")->" << fname << index << "; }" << std::endl;
    if (!is_RO)
        out_file << "            static inline void set(" << index_hdr_ex << "uint32_t value) { reinterpret_cast<" <<
                    name << "_t*>(" << base << ")->" << fname << index << " = value; }" << std::endl;

    if (has_bit_fileds)
        write_field_flags_operators(is_RO, name, base, field.name, multiple_regs);
    if (field.type.find("uint32_t") != std::string::npos)
        for (REG_FIELD_MASKS_t& mask : field.masks)
        {
            if (mask.bits < 2)
                continue;
            out_file << "            static inline uint32_t get_" << mask.name << "(" << index_hdr << ") { return reinterpret_cast<" << io_mode <<
                        field.name << "_t*>(&reinterpret_cast<" << name << "_t*>(" << base << ")->" << fname <<
                        index << ")->" << mask.name << "; }" << std::endl;
            if (!is_RO)
                out_file << "            static inline void set_" << mask.name << "(" << index_hdr_ex << "uint32_t value) { reinterpret_cast<" << io_mode <<
                            field.name << "_t*>(&reinterpret_cast<" << name << "_t*>(" << base << ")->" << fname <<
                            index << ")->" << mask.name << " = value; }" << std::endl;
        }
}

void write_field(REG_t& reg, REG_FIELD_t& field, std::string base)
{
    std::string name;
    if (reg.sub_name.size())
        name = reg.sub_name;
    else
        name = reg.name;

    if (to_upper(field.name).find("RESERVED") != std::string::npos)
        return;
    out_file << "        class " << field.name << std::endl;
    out_file << "        {" << std::endl;
    bool has_bit_fileds = false;
    if (field.type.find("uint32_t") != std::string::npos)
    {
        // bit/numeric fields
        out_file << "        private:" << std::endl;
        has_bit_fileds = write_field_bits(field);
        out_file << "        public:" << std::endl;
    }
    else
    {
        // structured fields
        out_file << "        public:" << std::endl;
    }

    write_field_enum(field);
    wfite_field_accs(field, base, name, has_bit_fileds, reg.base_num.size());

    out_file << "        };" << std::endl;
}

void write_reg_fields(REG_t& reg)
{
    std::string name;
    if (reg.sub_name.size())
        name = reg.sub_name;
    else
        name = reg.name;

    out_file << "        struct " << name << "_t" << std::endl;
    out_file << "        {" << std::endl;
    //fields_t& fields = reg.fields_array[0];
    for (REG_FIELD_t& field : reg.fields)
    {
        std::string type = field.type;
        size_t pos;
        if ((pos = type.find("_TypeDef")) != std::string::npos)
            type.erase(pos, 8);
        out_file << "            " << std::setw(FIELD_NAME_WIDTH) << std::left << type << field.name << field.array_size << ";" << std::endl;
    }
    out_file << "        };" << std::endl;
}

std::map<std::string,std::string> base_alias = {
    {"FSMC_Bank1", "FSMC_Bank1_R"},
    {"FSMC_Bank1E", "FSMC_Bank1E_R"},
    {"FSMC_Bank2_3", "FSMC_Bank2_3_R"},
    {"FSMC_Bank4", "FSMC_Bank4_R"},
};

void write_REGs()
{
    out_file << "namespace STM" << stm.bits << "_REGS" << std::endl;
    out_file << "{" << std::endl;
    for (std::string& str : stm.regs_defs)
        out_file << "    #define " << str << "_SUPPORT" << std::endl;
    out_file << std::endl;
    std::cout << "WR:" << std::endl;
    for (REG_t &reg : stm.regs)
    {
        std::string name;
        if (reg.sub_name.size())
            name = reg.sub_name;
        else
            name = reg.name;

        out_file << "    /* " << name << " DEFINITION */" << std::endl;
        std::string base_label;
        if (base_alias.count(name))
            base_label = to_upper("STM" + stm.bits + "::" + base_alias[name] + "_BASE");
        else
            base_label = to_upper("STM" + stm.bits + "::" + name + "_BASE");
        out_file << "    class " << name << std::endl;
        out_file << "    {" << std::endl;
        out_file << "    private:" << std::endl;
        if ((name.find("CAN") != std::string::npos) || (name.find("USB_OTG") != std::string::npos))
        {
            //out_file << "#warning TODO: " << name << std::endl;
        }
        else
        {
            write_reg_fields(reg);
            out_file << "    public:" << std::endl;
            for (REG_FIELD_t& field : reg.fields)
                write_field(reg, field, base_label);
        }
        out_file << "    };" << std::endl;

    }
    out_file << "}" << std::endl;
    out_file << std::endl;
}

void write_footer()
{
    out_file << "#endif /* __STM" << stm.bits << "F" << stm.chip << "xx_H */" << std::endl;
    out_file << std::endl;
}

int main(int argc, char** argv)
{
    if ((argc < 2) || (!probe_open_file(argv[1])))
    {
        std::cout << "Usage:" << std::endl << "\th_parser <header file name>" << std::endl;
        return 0;
    }
    prepare_input();
    EStage stage = EStage::IFNDEF;
    REG_t reg;
    int syn_start, syn_end;
    for (size_t i=0 ; i<in_strs.size() ; ++i)
    {
        switch (stage)
        {
            case EStage::IFNDEF:
            if (parse_header(in_strs[i]))
                stage = EStage::CORE_DEF;
            break;
        case EStage::CORE_DEF:
            if (parse_core_defs(in_strs[i]))
                    stage = EStage::IRQs;
            break;
        case EStage::IRQs:
            if (parse_IRQs(in_strs[i]))
                stage = EStage::INCLUDES;
            break;
        case EStage::INCLUDES:
            if (parse_includes(in_strs[i]))
                stage = EStage::REGS;
            break;
        case EStage::REGS:
            if (parse_regs(in_strs[i], reg))
            {
                --i;
                stage = EStage::BASES;
            }
            break;
        case EStage::BASES:
            if (parse_BASEs(in_strs[i]))
            {
                syn_start = i;
                --i;
                stage = EStage::FIELDS;
            }
            break;
        case EStage::FIELDS:
            if (parse_sync(in_strs[i]))
            {
                syn_end = i;
                for (int j=syn_start ; j<syn_end ; ++j)
                    parse_fields(in_strs[j]);
                stage = EStage::DEF_IS;
            }
            break;
        case EStage::DEF_IS:
            if ((in_strs[i].size()) && (in_strs[i].find("#define IS_") == std::string::npos))
            {
                --i;
                stage = EStage::CONSTS;
            }
            break;
        case EStage::CONSTS:
            if (parse_consts(in_strs[i]))
                    stage = EStage::END;
            break;
        case EStage::TYPEDEFS:
        case EStage::END:
            break;
        }
    }

    out_file.open(std::string(argv[1]) + "pp");
    write_header();
    write_defines();
    write_IRQs();
    write_BASEs();
    write_REGs();
    write_footer();
    out_file.close();
    return 0;
}
