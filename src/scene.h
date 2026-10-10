/* Provisional names: g_XXXX = DGROUP offset XXXX; fn_SEG_OFF = function at SEG:OFF in orig/MM3.EXE. CODE_4 = scene.c */
typedef unsigned char u8;
typedef unsigned int u16;

struct map { u16 cell[16][16]; u8 b200[16][16]; u8 b300[8]; u8 b308, b309; u8 b30a[3]; u8 b30d; u8 b30e[5]; u8 b313; u8 b314[12]; u8 b320[0x20]; };
extern struct map g_c554[];                     /* 0x340-byte map records */
extern char map_size_check[sizeof(struct map) == 0x340 ? 1 : -1];

extern u8 g_015b, g_acce, g_c4a2, g_c4a3, g_c4a4, g_c520, g_00ac, g_c52b, g_c500;
extern int g_acd4[];
extern long g_abda, g_c536, g_e8c6, g_ac18, g_a77a;
extern u8 g_e8f4, g_e8f5, g_e8f6, g_e8fc, g_014a, g_014b, g_014c, g_014d, g_b9d5;
extern int g_ec3a, g_ec3c, g_ec3e, g_ec40;
extern char g_d667, g_c53e;
extern u8 g_274e[], g_2600[], g_2604[];

void far fn_203f_000e(void);
void far fn_1e40_0007(void);
void far ovr_1839_0020(void);
void far fn_1903_05d8(void);
int far fn_1523_01ba(int);
void far fn_1523_0238(u8 *p, u16 bit, int set);
int far fn_1523_00cc(u8 *p, u16 bit);

void far fn_1b66_0b35(void);
int far fn_1b66_033e(register u16 v);

/* 07de */
extern int g_1438[][44], g_1598[][44];     /* 0x58-byte rows */
extern char g_12c8[][46], g_1380[][46];      /* per-facing x / y offsets */
/* 0889 / 0adc */
extern u8 g_017e, g_e8c1;
extern int g_ec38;
int far fn_1b66_0707(register int x, int y, u16 mask);
extern u8 g_8d60, g_8d61, g_8ef2, g_8ef3, g_92f5, g_a746, g_a76e, g_abb3, g_abb6, g_abb7, g_abb8, g_abb9, g_abbe, g_abbf, g_abc0, g_abc1, g_abde, g_abdf, g_abe0, g_abe1, g_abe2, g_abe4, g_abe5, g_abe6, g_abe7, g_abe8, g_abe9, g_abea, g_abeb, g_abf0, g_abf1, g_abf2, g_abf3, g_abf4, g_abf5, g_abf6, g_abf7, g_abf8, g_abf9, g_abfa, g_abfb, g_abfc, g_abfd, g_abfe, g_abff, g_ac00, g_ac03, g_ac04, g_ac05, g_ac06, g_ac07, g_ac08, g_ac09, g_ac0a, g_ac0b, g_ac0c, g_ac0d, g_ac0e, g_ac0f, g_ac10, g_ac11, g_ac12, g_ac13, g_ac1c, g_ac1d, g_ac1e, g_ac1f, g_ac20, g_ac24, g_ac25, g_ac26, g_acc2, g_acc3, g_acc4, g_acc5, g_acc6, g_acc7, g_acc8, g_acc9, g_acca, g_acd5, g_ad4e, g_ad4f, g_ad50, g_ad51, g_ad52, g_ad53, g_ad60, g_ad61, g_ad62, g_b98e, g_b98f, g_b9b8, g_b9b9, g_b9ba, g_b9c3, g_b9c6, g_b9c7, g_b9c8, g_b9d5, g_c47d, g_c47e, g_c498, g_c49d, g_c4c8, g_c4d7, g_c4fc, g_c4fd, g_c4fe, g_c4ff, g_c501, g_c502, g_c503, g_c504, g_c505, g_c506, g_c507, g_c508, g_c50e, g_c50f, g_c510, g_c511, g_c512, g_c513, g_c514, g_c515, g_c52a, g_c52c, g_c53a, g_c53b, g_c53c, g_c53d, g_d665, g_d666, g_d668, g_d669, g_d66a, g_d66b, g_e8b8, g_e8b9, g_e8be, g_e8bf, g_e8c0, g_ec80, g_ec81, g_ec86, g_ec87, g_ec89, g_ec8a, g_ec91, g_ec92, g_ec94, g_ec95, g_ec97, g_ec98, g_ec99, g_ec9a, g_ec9b, g_ec9c, g_ec9d, g_ec9e, g_ec9f, g_eca0, g_eca1, g_eca2, g_eca6, g_ecac, g_ecad, g_ecae, g_ecaf, g_ecb0, g_ecb1, g_ecb2, g_ecd2, g_ecd3, g_ecd4, g_ecd5, g_ecd6, g_ecd7, g_ecd8, g_ecd9, g_ecda, g_ece1, g_ece4, g_ece5, g_ece6, g_ece7, g_ecf7, g_ecf8, g_ed73;
/* 24dd */
extern u8 g_0185, g_015d, g_ac26, g_ece5, g_acc5, g_c4d7, g_ece6, g_ad4e, g_c52a;
extern u8 g_0e71[], g_0e73[], g_0e75[], g_0e77[], g_00dd[], g_00e5[], g_00ed[], g_00f5[];
extern int g_0142[];
extern u8 g_b9bb[], g_ab52[];
extern long g_c4ae, g_c4aa, g_a742;
int *far fn_1523_33fa(int *o);
int *far fn_1523_39c1(int *o);
void far fn_1903_213b(int);
/* 0b35 */
extern u8 g_017f, g_c52c;
void far fn_1523_0920(void);
void far fn_1523_0f7d(void);
void far fn_1903_2328(void);
extern u8 ;
