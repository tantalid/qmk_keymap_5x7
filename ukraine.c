
#pragma once

// -------------------------------- CIRILYK ukrainian
// clang-format off
enum unicode_names {
    UA_AL,
    UA_AU,
    UA_BL,
    UA_BU,
    UA_VL,
    UA_VU,
    UA_HEL,
    UA_HEU,
    UA_GEL,
    UA_GEU,
    UA_DL,
    UA_DU,
    UA_EL,
    UA_EU,
    UA_YEL,
    UA_YEU,
    UA_ZHL,
    UA_ZHU,
    UA_ZL,
    UA_ZU,
    UA_YL,
    UA_YU,
    UA_IL,
    UA_IU,
    UA_YIL,
    UA_YIU,
    UA_YOTL,
    UA_YOTU,
    UA_KL,
    UA_KU,
    UA_LL,
    UA_LU,
    UA_ML,
    UA_MU,
    UA_NL,
    UA_NU,
    UA_OL,
    UA_OU,
    UA_PL,
    UA_PU,
    UA_RL,
    UA_RU,
    UA_SL,
    UA_SU,
    UA_TL,
    UA_TU,
    UA_UL,
    UA_UU,
    UA_FL,
    UA_FU,
    UA_KHL,
    UA_KHU,
    UA_TSEL,
    UA_TSEU,
    UA_CHEL,
    UA_CHEU,
    UA_SHL,
    UA_SHU,
    UA_SHCHL,
    UA_SHCHU,
    UA_SOFT,
    UA_HARD,
    UA_YUL,
    UA_YUU,
    UA_YAL,
    UA_YAU,
    UA_YRL,
    UA_YRU,
    UA_YOL,
    UA_YOU,
    UA_ERUL,
    UA_ERUU,
    UA_APOST, // '
    UA_UAH, // ₴
    UA_NUM, // №
};

const uint32_t unicode_map[] PROGMEM = {
    [UA_AL]   = 0x0430,  // а
    [UA_AU]   = 0x0410,  // А
    [UA_BL]   = 0x0431,  // б
    [UA_BU]   = 0x0411,  // Б
    [UA_VL]   = 0x0432,  // в
    [UA_VU]   = 0x0412,  // В
    [UA_HEL]  = 0x0433,  // г
    [UA_HEU]  = 0x0413,  // Г
    [UA_GEL]  = 0x0491,  // ґ
    [UA_GEU]  = 0x0490,  // ґ
    [UA_DL]   = 0x0434,  // д
    [UA_DU]   = 0x0414,  // Д
    [UA_EL]   = 0x0435,  // е
    [UA_EU]   = 0x0415,  // Е
    [UA_YEL]   = 0x0454,  // є
    [UA_YEU]   = 0x0404,  // Є
    [UA_ZHL]   = 0x0436,  // ж
    [UA_ZHU]   = 0x0416,  // Ж
    [UA_ZL]    = 0x0437,  // з
    [UA_ZU]    = 0x0417,  // З
    [UA_YL]    = 0x0438,  // и
    [UA_YU]    = 0x0418,  // И
    [UA_IL]    = 0x0456,  // і
    [UA_IU]    = 0x0406,  // І
    [UA_YIL]   = 0x0457,  // ї
    [UA_YIU]   = 0x0407,  // Ї
    [UA_YOTL]  = 0x0439,  // й
    [UA_YOTU]  = 0x0419,  // Й
    [UA_KL]    = 0x043A,  // к
    [UA_KU]    = 0x041A,  // К
    [UA_LL]    = 0x043B,  // л
    [UA_LU]    = 0x041B,  // Л
    [UA_ML]    = 0x043C,  // м
    [UA_MU]    = 0x041C,  // М
    [UA_NL]    = 0x043D,  // н
    [UA_NU]    = 0x041D,  // Н
    [UA_OL]    = 0x043E,  // о
    [UA_OU]    = 0x041E,  // О
    [UA_PL]    = 0x043F,  // п
    [UA_PU]    = 0x041F,  // П
    [UA_RL]    = 0x0440,  // р
    [UA_RU]    = 0x0420,  // Р
    [UA_SL]    = 0x0441,  // с
    [UA_SU]    = 0x0421,  // С
    [UA_TL]    = 0x0442,  // т
    [UA_TU]    = 0x0422,  // Т
    [UA_UL]    = 0x0443,  // у
    [UA_UU]    = 0x0423,  // У
    [UA_FL]    = 0x0444,  // ф
    [UA_FU]    = 0x0424,  // Ф
    [UA_KHL]   = 0x0445,  // х
    [UA_KHU]   = 0x0425,  // Х
    [UA_TSEL]  = 0x0446,  // ц
    [UA_TSEU]  = 0x0426,  // Ц
    [UA_CHEL]  = 0x0447,  // ч
    [UA_CHEU]  = 0x0427,  // Ч
    [UA_SHL]   = 0x0448,  // ш
    [UA_SHU]   = 0x0428,  // Ш
    [UA_SHCHL] = 0x0449,  // щ
    [UA_SHCHU] = 0x0429,  // Щ
    [UA_SOFT]  = 0x044C,  // Ь
    [UA_HARD]  = 0x044A,  // ъ
    [UA_YUL]   = 0x044E,  // ю
    [UA_YUU]   = 0x042E,  // Ю
    [UA_YAL]   = 0x044F,  // я
    [UA_YAU]   = 0x042F,  // Я
    [UA_YRL]   = 0x044B,  // ы
    [UA_YRU]   = 0x042B,  // Ы
    [UA_YOL]   = 0x0451,  // ё
    [UA_YOU]   = 0x0401,  // Ё
    [UA_ERUL]  = 0x044D,  // э
    [UA_ERUU]  = 0x042D,  // Э
    [UA_APOST] = 0x0027,  // '
    [UA_UAH]   = 0x20B4,  // ₴
    [UA_NUM]   = 0x2116,  // №
};


#define UA_A    XP(UA_AL,   UA_AU)    // А
#define UA_B    XP(UA_BL,   UA_BU)    // Б
#define UA_V    XP(UA_VL,   UA_VU)    // В
#define UA_HE   XP(UA_HEL,  UA_HEU)   // Г
#define UA_GE   XP(UA_GEL,  UA_GEU)   // ґ
#define UA_D    XP(UA_DL,   UA_DU)    // Д
#define UA_E    XP(UA_EL,   UA_EU)    // Е
#define UA_YE   XP(UA_YEL,  UA_YEU)   // Є
#define UA_ZH   XP(UA_ZHL,  UA_ZHU)   // Ж
#define UA_Z    XP(UA_ZL,   UA_ZU)    // З
#define UA_Y    XP(UA_YL,   UA_YU)    // И
#define UA_I    XP(UA_IL,   UA_IU)    // І
#define UA_YI   XP(UA_YIL,  UA_YIU)   // Ї
#define UA_YOT  XP(UA_YOTL, UA_YOTU)  // Й
#define UA_K    XP(UA_KL,   UA_KU)    // К
#define UA_L    XP(UA_LL,   UA_LU)    // Л
#define UA_M    XP(UA_ML,   UA_MU)    // М
#define UA_N    XP(UA_NL,   UA_NU)    // Н
#define UA_O    XP(UA_OL,   UA_OU)    // О
#define UA_P    XP(UA_PL,   UA_PU)    // П
#define UA_R    XP(UA_RL,   UA_RU)    // Р
#define UA_S    XP(UA_SL,   UA_SU)    // С
#define UA_T    XP(UA_TL,   UA_TU)    // Т
#define UA_U    XP(UA_UL,   UA_UU)    // У
#define UA_F    XP(UA_FL,   UA_FU)    // Ф
#define UA_KH   XP(UA_KHL,  UA_KHU)   // Х
#define UA_TSE  XP(UA_TSEL, UA_TSEU)  // Ц
#define UA_CHE  XP(UA_CHEL, UA_CHEU)  // Ч
#define UA_SH   XP(UA_SHL,  UA_SHU)   // Ш
#define UA_SHCH XP(UA_SHCHL,UA_SHCHU) // Щ
#define UA_SOFT XP(UA_SOFT, UA_HARD)  // Ь/ъ
#define UA_YU   XP(UA_YUL,  UA_YUU)   // Ю
#define UA_YA   XP(UA_YAL,  UA_YAU)   // Я
#define UA_YR   XP(UA_YRL,  UA_YRU)   // Ы
#define UA_YO   XP(UA_YOL,  UA_YOU)   // Ё
#define UA_ERU  XP(UA_ERUL, UA_ERUU)  // Э
#define UA_YOYR XP(UA_YRL,  UA_YOL)   // Ы/Ё
#define UA_APOS XP(UA_APOST,UA_UAH)   // '/₴


// -------------------------------- end ukrainian
