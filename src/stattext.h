/* stattext.h: CODE_6 (root segment 103f). g_XXXX = DGROUP offset XXXX; fn_SEG_OFF = function at SEG:OFF. */
typedef unsigned char u8;
typedef unsigned int u16;

struct anim { u16 frame; int type; char pad[8]; };     /* 12-byte object records */
extern struct anim g_a794[];

/* own _DATA (statd.inc) */
extern int g_1724, g_1726;
extern u8 g_1728[2], g_172a[2], g_172c[2], g_172e[2], g_1730[2], g_1732[2], g_1734[2], g_1736[2], g_1738[2], g_173a[2];

extern u8 g_00aa, g_00ac, g_00af, g_0121, g_0122, g_0123, g_017f, g_0180, g_0185, g_c4a2, g_c4c6, g_c520, g_c52b,
	g_e8f4, g_e8f5, g_e8f6, g_ece0, g_ed72;
extern char g_e8c1;
extern u8 g_ab52[], g_b9bb[], g_1a6c[], g_2815[], g_00bb[], g_00dd[], g_00e5[], g_00ed[], g_00f5[];
extern int g_b810[], g_b6bc[], g_0142[], g_0165[], g_d66e[];
extern u16 g_b018[];
extern long g_ecc4, g_ec8c, g_a742, g_c4a6[];
extern char g_ac27[], g_d256[], g_acd6[];
extern char g_12c8[][46], g_1380[][46];      /* per-facing x / y offsets */

void far fn_203f_000e(void);
void far fn_203f_006a(void);
void far fn_1b66_0889(void);
void far fn_1b66_0adc(void);
void far fn_1523_0920(void);
void far fn_1523_0f7d(void);
void far fn_1903_2328(void);
int far fn_1b66_05b5(int, int, int);
int *far fn_1523_2209(register int *o);
int *far fn_1523_2d08(register int *o);
int *far fn_1523_33fa(int *o);
int *far fn_1523_39c1(int *o);
void far fn_1903_213b(int);
void far fn_1903_2168(int *o);
void far fn_124f_2ac5(char far *);
void far fn_124f_2acf(int, int);
void far fn_1511_1575(void *);
void far fn_1b66_0071(void);
void *far memset(void *, int, unsigned);
int far sprintf(char *, const char *, ...);
