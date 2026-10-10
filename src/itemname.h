/* itemname.h: CODE_5 (root segment 0e40). g_XXXX = DGROUP offset XXXX; fn_SEG_OFF = function at SEG:OFF. */
typedef unsigned char u8;
typedef unsigned int u16;

struct anim { u16 frame; int type; char pad[8]; };     /* 12-byte object records */
extern struct anim g_a794[];

extern u8 g_00aa, g_00ac, g_0121, g_0122, g_0123, g_015d, g_0180, g_0185, g_8d60, g_8d61, g_8ef2, g_8ef3, g_92f5,
	g_a746, g_a76e, g_abb3, g_abb6, g_abb7, g_abbe, g_abbf, g_abc0, g_abc1, g_abde, g_abdf, g_abe2, g_abf2, g_abf7,
	g_abf8, g_abf9, g_abfa, g_abff, g_ac00, g_ac03, g_ac04, g_ac05, g_ac06, g_ac07, g_ac0a, g_ac0b, g_ac0c, g_ac0f,
	g_ac10, g_ac11, g_ac12, g_ac13, g_ac1c, g_ac1d, g_ac1e, g_ac1f, g_ac20, g_ac24, g_ac25, g_ac26, g_acc2, g_acc3,
	g_acc4, g_acc5, g_acc6, g_acc7, g_acc8, g_acc9, g_acca, g_acd5, g_ad4e, g_ad4f, g_ad50, g_ad51, g_ad52, g_ad53,
	g_ad60, g_ad61, g_ad62, g_b98e, g_b98f, g_b9b8, g_b9b9, g_b9ba, g_b9c3, g_b9c6, g_b9c7, g_b9c8, g_c47d, g_c47e,
	g_c498, g_c49d, g_c4a2, g_c4c6, g_c4c8, g_c4d7, g_c4fc, g_c4fd, g_c501, g_c502, g_c505, g_c506, g_c50e, g_c50f,
	g_c512, g_c513, g_c520, g_c52a, g_c53a, g_c53b, g_c53c, g_c53d, g_d665, g_d666, g_d668, g_d669, g_d66a, g_d66b,
	g_e8b8, g_e8b9, g_e8be, g_e8bf, g_e8c0, g_e8c1, g_ec80, g_ec81, g_ec86, g_ec87, g_ec89, g_ec8a, g_ec94, g_ec95,
	g_ec97, g_ec9a, g_ec9b, g_ec9c, g_ec9d, g_ec9e, g_ec9f, g_eca0, g_eca1, g_eca2, g_eca6, g_ecac, g_ecad, g_ecae,
	g_ecaf, g_ecb0, g_ecb1, g_ecb2, g_ecd2, g_ecd3, g_ecd4, g_ecd5, g_ecd6, g_ecd7, g_ecd8, g_ecd9, g_ecda, g_ece0,
	g_ece1, g_ece4, g_ece5, g_ece6, g_ece7, g_ecf7, g_ecf8, g_ed72, g_ed73;
extern u8 g_ab52[], g_b9bb[], g_1a6c[], g_2815[], g_00bb[], g_0e61[], g_0e77[];
extern int g_b810[], g_b6bc[], g_0142[], g_d66e[];
extern u16 g_b018[];
extern long g_ecc4, g_c4b6, g_c4b2, g_a742;
extern char g_ac27[], g_d256[], g_acd6[];

void far fn_1e40_0007(void);
int *far fn_1523_2209(register int *o);
int *far fn_1523_2d08(register int *o);
void far fn_1903_213b(int);
void far fn_1903_2168(int *o);
void far fn_124f_2ac5(char far *);
void far fn_124f_2acf(int, int);
void far fn_1511_1575(void *);
void far fn_1b66_0071(void);
void far fn_1b66_24dd(register int *o);
void *far memset(void *, int, unsigned);
int far sprintf(char *, const char *, ...);
