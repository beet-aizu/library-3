---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/rolling_hash_u64.cpp\"\nusing u64 = unsigned long\
    \ long;\n\nconstexpr u64 M = (1UL << 61) - 1;\nconstexpr u64 POSITIVISER = M *\
    \ 3;\nconstexpr u64 MASK30 = (1UL << 30) - 1;\nconstexpr u64 MASK31 = (1UL <<\
    \ 31) - 1;\n\nclass rolling_hash_u64 {\n    static u64 get_base(){\n        u64\
    \ z = (static_cast<uint64_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL\
    \ << 32)-1)))+0x9e3779b97f4a7c15;\n        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;\n        return z;\n    }\n\
    \n    static u64 &B() {\n        static u64 B_ = (get_base())%(M-2)+2;\n     \
    \   return B_;\n    }\n    static vector<u64> &p() {\n        static vector<u64>\
    \ p_{1, B()};\n        return p_;\n    }\n\n    static inline u64 mul(u64 x, u64\
    \ y){\n        u64 a = x >> 31, b = x & MASK31, c = y >> 31, d = y & MASK31, e\
    \ = b*c+a*d;\n        return (a*c << 1) + b*d + ((e & MASK30) << 31) + (e >> 30);\n\
    \    }\n\n    static inline u64 calc_mod(u64 val){\n        val = (val & M) +\
    \ (val >> 61);\n        if(val > M) val -= M;\n        return val;\n    }\npublic:\n\
    \    vector<u64> hash;\n    explicit rolling_hash_u64(const string &s) {\n   \
    \     if(p().size() <= s.size()){\n            int l = p().size();\n         \
    \   p().resize(s.size()+1);\n            for (int i = l; i < p().size(); ++i)\
    \ {\n                p()[i] = calc_mod(mul(p()[i-1], p()[1]));\n            }\n\
    \        }\n        hash.resize(s.size()+1, 0);\n        for (int i = 0; i < s.size();\
    \ ++i) {\n            hash[i+1] = calc_mod(mul(hash[i],B()) + s[i]);\n       \
    \ }\n    };\n\n    u64 get(int l, int r){\n        return calc_mod(hash[r] + POSITIVISER\
    \ - mul(hash[l], p()[r-l]));\n    }\n};\n\n"
  code: "using u64 = unsigned long long;\n\nconstexpr u64 M = (1UL << 61) - 1;\nconstexpr\
    \ u64 POSITIVISER = M * 3;\nconstexpr u64 MASK30 = (1UL << 30) - 1;\nconstexpr\
    \ u64 MASK31 = (1UL << 31) - 1;\n\nclass rolling_hash_u64 {\n    static u64 get_base(){\n\
    \        u64 z = (static_cast<uint64_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL\
    \ << 32)-1)))+0x9e3779b97f4a7c15;\n        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;\n        return z;\n    }\n\
    \n    static u64 &B() {\n        static u64 B_ = (get_base())%(M-2)+2;\n     \
    \   return B_;\n    }\n    static vector<u64> &p() {\n        static vector<u64>\
    \ p_{1, B()};\n        return p_;\n    }\n\n    static inline u64 mul(u64 x, u64\
    \ y){\n        u64 a = x >> 31, b = x & MASK31, c = y >> 31, d = y & MASK31, e\
    \ = b*c+a*d;\n        return (a*c << 1) + b*d + ((e & MASK30) << 31) + (e >> 30);\n\
    \    }\n\n    static inline u64 calc_mod(u64 val){\n        val = (val & M) +\
    \ (val >> 61);\n        if(val > M) val -= M;\n        return val;\n    }\npublic:\n\
    \    vector<u64> hash;\n    explicit rolling_hash_u64(const string &s) {\n   \
    \     if(p().size() <= s.size()){\n            int l = p().size();\n         \
    \   p().resize(s.size()+1);\n            for (int i = l; i < p().size(); ++i)\
    \ {\n                p()[i] = calc_mod(mul(p()[i-1], p()[1]));\n            }\n\
    \        }\n        hash.resize(s.size()+1, 0);\n        for (int i = 0; i < s.size();\
    \ ++i) {\n            hash[i+1] = calc_mod(mul(hash[i],B()) + s[i]);\n       \
    \ }\n    };\n\n    u64 get(int l, int r){\n        return calc_mod(hash[r] + POSITIVISER\
    \ - mul(hash[l], p()[r-l]));\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: string/rolling_hash_u64.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/rolling_hash_u64.cpp
layout: document
redirect_from:
- /library/string/rolling_hash_u64.cpp
- /library/string/rolling_hash_u64.cpp.html
title: string/rolling_hash_u64.cpp
---