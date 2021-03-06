static const std::string kCodepageASCII =
        "U+0000-U+007F";

static const std::string kCodepage437 = // OEM 437
        "U+0000, U+263A, U+263B, U+2665, U+2666, U+2663, U+2660, U+2022,"
        "U+25D8, U+25CB, U+25D9, U+2642, U+2640, U+266A, U+266B, U+263C,"
        "U+25BA, U+25C4, U+2195, U+203C, U+00B6, U+00A7, U+25AC, U+21A8,"
        "U+2191, U+2193, U+2192, U+2190, U+221F, U+2194, U+25B2, U+25BC,"
        "U+0020-U+007F,"
        "U+00C7, U+00FC, U+00E9, U+00E2, U+00E4, U+00E0, U+00E5, U+00E7,"
        "U+00EA, U+00EB, U+00E8, U+00EF, U+00EE, U+00EC, U+00C4, U+00C5,"
        "U+00C9, U+00E6, U+00C6, U+00F4, U+00F6, U+00F2, U+00FB, U+00F9,"
        "U+00FF, U+00D6, U+00DC, U+00A2, U+00A3, U+00A5, U+20A7, U+0192,"
        "U+00E1, U+00ED, U+00F3, U+00FA, U+00F1, U+00D1, U+00AA, U+00BA,"
        "U+00BF, U+2310, U+00AC, U+00BD, U+00BC, U+00A1, U+00AB, U+00BB,"
        "U+2591, U+2592, U+2593, U+2502, U+2524, U+2561, U+2562, U+2556,"
        "U+2555, U+2563, U+2551, U+2557, U+255D, U+255C, U+255B, U+2510,"
        "U+2514, U+2534, U+252C, U+251C, U+2500, U+253C, U+255E, U+255F,"
        "U+255A, U+2554, U+2569, U+2566, U+2560, U+2550, U+256C, U+2567,"
        "U+2568, U+2564, U+2565, U+2559, U+2558, U+2552, U+2553, U+256B,"
        "U+256A, U+2518, U+250C, U+2588, U+2584, U+258C, U+2590, U+2580,"
        "U+03B1, U+00DF, U+0393, U+03C0, U+03A3, U+03C3, U+00B5, U+03C4,"
        "U+03A6, U+0398, U+03A9, U+03B4, U+221E, U+03C6, U+03B5, U+2229,"
        "U+2261, U+00B1, U+2265, U+2264, U+2320, U+2321, U+00F7, U+2248,"
        "U+00B0, U+2219, U+00B7, U+221A, U+207F, U+00B2, U+25A0, U+00A0";

static const std::string kCodepage866 = // DOS Cyrilic
        "U+0000-U+007F,"
        "U+0410, U+0411, U+0412, U+0413, U+0414, U+0415, U+0416, U+0417,"
        "U+0418, U+0419, U+041a, U+041b, U+041c, U+041d, U+041e, U+041f,"
        "U+0420, U+0421, U+0422, U+0423, U+0424, U+0425, U+0426, U+0427,"
        "U+0428, U+0429, U+042a, U+042b, U+042c, U+042d, U+042e, U+042f,"
        "U+0430, U+0431, U+0432, U+0433, U+0434, U+0435, U+0436, U+0437,"
        "U+0438, U+0439, U+043a, U+043b, U+043c, U+043d, U+043e, U+043f,"
        "U+2591, U+2592, U+2593, U+2502, U+2524, U+2561, U+2562, U+2556,"
        "U+2555, U+2563, U+2551, U+2557, U+255d, U+255c, U+255b, U+2510,"
        "U+2514, U+2534, U+252c, U+251c, U+2500, U+253c, U+255e, U+255f,"
        "U+255a, U+2554, U+2569, U+2566, U+2560, U+2550, U+256c, U+2567,"
        "U+2568, U+2564, U+2565, U+2559, U+2558, U+2552, U+2553, U+256b,"
        "U+256a, U+2518, U+250c, U+2588, U+2584, U+258c, U+2590, U+2580,"
        "U+0440, U+0441, U+0442, U+0443, U+0444, U+0445, U+0446, U+0447,"
        "U+0448, U+0449, U+044a, U+044b, U+044c, U+044d, U+044e, U+044f,"
        "U+0401, U+0451, U+0404, U+0454, U+0407, U+0457, U+040e, U+045e,"
        "U+00b0, U+2219, U+00b7, U+221a, U+2116, U+00a4, U+25a0, U+00a0";

static const std::string kCodepage1250 = // Windows Central European
        "U+0000-U+007F,"
        "U+20AC, U+FFFE, U+201A, U+FFFE, U+201E, U+2026, U+2020, U+2021,"
        "U+FFFE, U+2030, U+0160, U+2039, U+015A, U+0164, U+017D, U+0179,"
        "U+FFFE, U+2018, U+2019, U+201C, U+201D, U+2022, U+2013, U+2014,"
        "U+FFFE, U+2122, U+0161, U+203A, U+015B, U+0165, U+017E, U+017A,"
        "U+00A0, U+02C7, U+02D8, U+0141, U+00A4, U+0104, U+00A6, U+00A7,"
        "U+00A8, U+00A9, U+015E, U+00AB, U+00AC, U+00AD, U+00AE, U+017B,"
        "U+00B0, U+00B1, U+02DB, U+0142, U+00B4, U+00B5, U+00B6, U+00B7,"
        "U+00B8, U+0105, U+015F, U+00BB, U+013D, U+02DD, U+013E, U+017C,"
        "U+0154, U+00C1, U+00C2, U+0102, U+00C4, U+0139, U+0106, U+00C7,"
        "U+010C, U+00C9, U+0118, U+00CB, U+011A, U+00CD, U+00CE, U+010E,"
        "U+0110, U+0143, U+0147, U+00D3, U+00D4, U+0150, U+00D6, U+00D7,"
        "U+0158, U+016E, U+00DA, U+0170, U+00DC, U+00DD, U+0162, U+00DF,"
        "U+0155, U+00E1, U+00E2, U+0103, U+00E4, U+013A, U+0107, U+00E7,"
        "U+010D, U+00E9, U+0119, U+00EB, U+011B, U+00ED, U+00EE, U+010F,"
        "U+0111, U+0144, U+0148, U+00F3, U+00F4, U+0151, U+00F6, U+00F7,"
        "U+0159, U+016F, U+00FA, U+0171, U+00FC, U+00FD, U+0163, U+02D9";

static const std::string kCodepage1251 = // Windows Cyrillic
        "U+0000-U+007F,"
        "U+0402, U+0403, U+201A, U+0453, U+201E, U+2026, U+2020, U+2021,"
        "U+20AC, U+2030, U+0409, U+2039, U+040A, U+040C, U+040B, U+040F,"
        "U+0452, U+2018, U+2019, U+201C, U+201D, U+2022, U+2013, U+2014,"
        "U+003F, U+2122, U+0459, U+203A, U+045A, U+045C, U+045B, U+045F,"
        "U+00A0, U+040E, U+045E, U+0408, U+00A4, U+0490, U+00A6, U+00A7,"
        "U+0401, U+00A9, U+0404, U+00AB, U+00AC, U+00AD, U+00AE, U+0407,"
        "U+00B0, U+00B1, U+0406, U+0456, U+0491, U+00B5, U+00B6, U+00B7,"
        "U+0451, U+2116, U+0454, U+00BB, U+0458, U+0405, U+0455, U+0457,"
        "U+0410, U+0411, U+0412, U+0413, U+0414, U+0415, U+0416, U+0417,"
        "U+0418, U+0419, U+041A, U+041B, U+041C, U+041D, U+041E, U+041F,"
        "U+0420, U+0421, U+0422, U+0423, U+0424, U+0425, U+0426, U+0427,"
        "U+0428, U+0429, U+042A, U+042B, U+042C, U+042D, U+042E, U+042F,"
        "U+0430, U+0431, U+0432, U+0433, U+0434, U+0435, U+0436, U+0437,"
        "U+0438, U+0439, U+043A, U+043B, U+043C, U+043D, U+043E, U+043F,"
        "U+0440, U+0441, U+0442, U+0443, U+0444, U+0445, U+0446, U+0447,"
        "U+0448, U+0449, U+044A, U+044B, U+044C, U+044D, U+044E, U+044F";

static const std::string kCodepageTCOD =
// First row
        "U+0020-U+003F,"
        // Second row
        "U+0040, U+005B-U+0060, U+007B-U+007E, U+2591-U+2593,"
        "U+2502, U+2500, U+253C, U+2524, U+2534, U+251C, U+252C, U+2514, U+250C, U+2510, U+2518,"
        "U+2598, U+259D, U+2580, U+2597, U+259A, U+2590, U+2596,"
        // Third row
        "U+2191, U+2193, U+2190, U+2192, U+25B2, U+25BC, U+25C4, U+25BA, U+2195, U+2194,"
        "U+2610, U+2611, U+26AA, U+26AB,"
        "U+2551, U+2550, U+256C, U+2563, U+2569, U+2560, U+2565, U+255A, U+2554, U+2557, U+255D,"
        "U+0020, U+0002-U+0007,"
        // Fourth row
        "U+0041-U+005A, U+0008-U+000D,"
        // Fifth row
        "U+0061-U+007A";
