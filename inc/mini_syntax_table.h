#include <limits.h>

#define TABLE_SIZE (UCHAR_MAX + 1)

#define META_CHARS "<>;|"
#define BREAK_CHARS "<>;| \t\n"
#define QUOTE_CHARS "\"\'"
#define EXP_CHARS "$"
#define BSDQUOTE_CHARS "\n\"$\\`"
#define XQUOTE_CHARS "\"\'\\"
#define SPECVAR_CHARS "?"
#define BLANK_CHARS "\t "
#define END_CHARS "\n\0"		/** Character which defines end of command line **/

/* Mandatory macros */
#define CWORD		0x0000	/* nothing special; an ordinary character */
#define CMETA		0x0001	/* bash: "&();<>|" */		/* minishell: ";<>|" */			/* shell meta character */
#define CBREAK		0x0002	/* bash: "\t\n &();<>|" */	/* minishell: "\t\n ;<>|" */	/* shell break character */
#define CQUOTE		0x0004	/* bash: "\"\'`" */			/* minishell: "\"\'" */			/* shell quote character */
#define CEXP		0x0008	/* bash: "$<>" */				/* minishell: "$" */		/* shell expansion character */
#define CBSDQUOTE	0x0010	/* bash: "\n" "\"" "\$" "\\" "\`" still to test*/	/* minishell: "\n" "\"" "\$" "\\" "\`" still to test */	/* characters escaped by backslash in double quotes */
#define CXQUOTE		0x0020	/* bash: "\"\'`\\" */		/* minishell: "\"\'\\" still to test */	/* quote + backslash */
#define CSPECVAR	0x0040	/* bash: "!#$*-?@" */		/* minishell: "?" */			/* single-character shell variable name */
#define CBLANK		0x0080	/* bash: "\t " */			/* minishell: "\t " */			/* whitespace (blank) character */
#define CEND		0x0100	/* bash: not included */	/* minishell: "\n\0" */			/* indicators for end of command transmission */

int		*populate_syntax_table(void);
void	analyze_token(t_token *token);
void	print_table(int *table);

// void	set_value(int *table, char *syntax_chars, int syntax_value);


/* Not mandatory macros */
// #define BACKQ		0x0004	/* bash: ` */				/* minishell: not mandatory */	/* back quote */
// #define SPECL		0x0010	/* bash: CTLESC, CTLNUL */	/* minishell: not mandatory */	/* special character that needs quoting */
// #define BSHDOC		0x0080	/* bash: "$\`" */		/* minishell: not mandatory */	/* characters escaped by backslash in here doc */
// #define GLOB		0x0100	/* bash: "*?\[]^" */		/* minishell: not mandatory */	/* globbing characters */
// #define XGLOB		0x0200	/* bash: "!*+?@" */		/* minishell: not mandatory */	/* extended globbing characters */
// #define SUBSTOP		0x1000	/* bash: "+-=?" */		/* minishell: not mandatory */	/* values of OP for ${word[:]OPstuff} */

// int sh_syntabsiz = 256;
// int sh_syntaxtab[256] = {
// 	WORD,		/* 0 */
// 	WORD,		/* CTLESC */
// 	WORD,		/* 2 */
// 	WORD,		/* 3 */
// 	WORD,		/* 4 */
// 	WORD,		/* 5 */
// 	WORD,		/* 6 */
// 	WORD,		/* \a */
// 	WORD,		/* \b */
// 	BREAK|BLANK,		/* \t */
// 	BREAK|BSDQUOTE,		/* \n */
// 	WORD,		/* \v */
// 	WORD,		/* \f */
// 	WORD,		/* \r */
// 	WORD,		/* 14 */
// 	WORD,		/* 15 */
// 	WORD,		/* 16 */
// 	WORD,		/* 17 */
// 	WORD,		/* 18 */
// 	WORD,		/* 19 */
// 	WORD,		/* 20 */
// 	WORD,		/* 21 */
// 	WORD,		/* 22 */
// 	WORD,		/* 23 */
// 	WORD,		/* 24 */
// 	WORD,		/* 25 */
// 	WORD,		/* 26 */
// 	WORD,		/* ESC */
// 	WORD,		/* 28 */
// 	WORD,		/* 29 */
// 	WORD,		/* 30 */
// 	WORD,		/* 31 */
// 	BREAK|BLANK,		/* SPC */
// 	WORD,		/* ! */
// 	QUOTE|BSDQUOTE|XQUOTE,		/* " */
// 	WORD,		/* # */
// 	EXP|BSDQUOTE|SPECVAR,		/* $ */
// 	WORD,		/* % */
// 	META|BREAK,		/* & */
// 	QUOTE|XQUOTE,		/* ' */
// 	META|BREAK,		/* ( */
// 	META|BREAK,		/* ) */
// 	WORD,		/* * */
// 	WORD,		/* + */
// 	WORD,		/* , */
// 	WORD,		/* - */
// 	WORD,		/* . */
// 	WORD,		/* / */
// 	WORD,		/* 0 */
// 	WORD,		/* 1 */
// 	WORD,		/* 2 */
// 	WORD,		/* 3 */
// 	WORD,		/* 4 */
// 	WORD,		/* 5 */
// 	WORD,		/* 6 */
// 	WORD,		/* 7 */
// 	WORD,		/* 8 */
// 	WORD,		/* 9 */
// 	WORD,		/* : */
// 	META|BREAK,		/* ; */
// 	META|BREAK,		/* < */
// 	WORD,		/* = */
// 	META|BREAK,		/* > */
// 	SPECVAR,		/* ? */
// 	WORD,		/* @ */
// 	WORD,		/* A */
// 	WORD,		/* B */
// 	WORD,		/* C */
// 	WORD,		/* D */
// 	WORD,		/* E */
// 	WORD,		/* F */
// 	WORD,		/* G */
// 	WORD,		/* H */
// 	WORD,		/* I */
// 	WORD,		/* J */
// 	WORD,		/* K */
// 	WORD,		/* L */
// 	WORD,		/* M */
// 	WORD,		/* N */
// 	WORD,		/* O */
// 	WORD,		/* P */
// 	WORD,		/* Q */
// 	WORD,		/* R */
// 	WORD,		/* S */
// 	WORD,		/* T */
// 	WORD,		/* U */
// 	WORD,		/* V */
// 	WORD,		/* W */
// 	WORD,		/* X */
// 	WORD,		/* Y */
// 	WORD,		/* Z */
// 	WORD,		/* [ */
// 	BSDQUOTE|XQUOTE,		/* \ */
// 	WORD,		/* ] */
// 	WORD,		/* ^ */
// 	WORD,		/* _ */
// 	WORD,		/* ` */
// 	WORD,		/* a */
// 	WORD,		/* b */
// 	WORD,		/* c */
// 	WORD,		/* d */
// 	WORD,		/* e */
// 	WORD,		/* f */
// 	WORD,		/* g */
// 	WORD,		/* h */
// 	WORD,		/* i */
// 	WORD,		/* j */
// 	WORD,		/* k */
// 	WORD,		/* l */
// 	WORD,		/* m */
// 	WORD,		/* n */
// 	WORD,		/* o */
// 	WORD,		/* p */
// 	WORD,		/* q */
// 	WORD,		/* r */
// 	WORD,		/* s */
// 	WORD,		/* t */
// 	WORD,		/* u */
// 	WORD,		/* v */
// 	WORD,		/* w */
// 	WORD,		/* x */
// 	WORD,		/* y */
// 	WORD,		/* z */
// 	WORD,		/* { */
// 	META|BREAK,		/* | */
// 	WORD,		/* } */
// 	WORD,		/* ~ */
// 	WORD,		/* CTLNUL */
// 	WORD,		/* 128 */
// 	WORD,		/* 129 */
// 	WORD,		/* 130 */
// 	WORD,		/* 131 */
// 	WORD,		/* 132 */
// 	WORD,		/* 133 */
// 	WORD,		/* 134 */
// 	WORD,		/* 135 */
// 	WORD,		/* 136 */
// 	WORD,		/* 137 */
// 	WORD,		/* 138 */
// 	WORD,		/* 139 */
// 	WORD,		/* 140 */
// 	WORD,		/* 141 */
// 	WORD,		/* 142 */
// 	WORD,		/* 143 */
// 	WORD,		/* 144 */
// 	WORD,		/* 145 */
// 	WORD,		/* 146 */
// 	WORD,		/* 147 */
// 	WORD,		/* 148 */
// 	WORD,		/* 149 */
// 	WORD,		/* 150 */
// 	WORD,		/* 151 */
// 	WORD,		/* 152 */
// 	WORD,		/* 153 */
// 	WORD,		/* 154 */
// 	WORD,		/* 155 */
// 	WORD,		/* 156 */
// 	WORD,		/* 157 */
// 	WORD,		/* 158 */
// 	WORD,		/* 159 */
// 	WORD,		/* 160 */
// 	WORD,		/* 161 */
// 	WORD,		/* 162 */
// 	WORD,		/* 163 */
// 	WORD,		/* 164 */
// 	WORD,		/* 165 */
// 	WORD,		/* 166 */
// 	WORD,		/* 167 */
// 	WORD,		/* 168 */
// 	WORD,		/* 169 */
// 	WORD,		/* 170 */
// 	WORD,		/* 171 */
// 	WORD,		/* 172 */
// 	WORD,		/* 173 */
// 	WORD,		/* 174 */
// 	WORD,		/* 175 */
// 	WORD,		/* 176 */
// 	WORD,		/* 177 */
// 	WORD,		/* 178 */
// 	WORD,		/* 179 */
// 	WORD,		/* 180 */
// 	WORD,		/* 181 */
// 	WORD,		/* 182 */
// 	WORD,		/* 183 */
// 	WORD,		/* 184 */
// 	WORD,		/* 185 */
// 	WORD,		/* 186 */
// 	WORD,		/* 187 */
// 	WORD,		/* 188 */
// 	WORD,		/* 189 */
// 	WORD,		/* 190 */
// 	WORD,		/* 191 */
// 	WORD,		/* 192 */
// 	WORD,		/* 193 */
// 	WORD,		/* 194 */
// 	WORD,		/* 195 */
// 	WORD,		/* 196 */
// 	WORD,		/* 197 */
// 	WORD,		/* 198 */
// 	WORD,		/* 199 */
// 	WORD,		/* 200 */
// 	WORD,		/* 201 */
// 	WORD,		/* 202 */
// 	WORD,		/* 203 */
// 	WORD,		/* 204 */
// 	WORD,		/* 205 */
// 	WORD,		/* 206 */
// 	WORD,		/* 207 */
// 	WORD,		/* 208 */
// 	WORD,		/* 209 */
// 	WORD,		/* 210 */
// 	WORD,		/* 211 */
// 	WORD,		/* 212 */
// 	WORD,		/* 213 */
// 	WORD,		/* 214 */
// 	WORD,		/* 215 */
// 	WORD,		/* 216 */
// 	WORD,		/* 217 */
// 	WORD,		/* 218 */
// 	WORD,		/* 219 */
// 	WORD,		/* 220 */
// 	WORD,		/* 221 */
// 	WORD,		/* 222 */
// 	WORD,		/* 223 */
// 	WORD,		/* 224 */
// 	WORD,		/* 225 */
// 	WORD,		/* 226 */
// 	WORD,		/* 227 */
// 	WORD,		/* 228 */
// 	WORD,		/* 229 */
// 	WORD,		/* 230 */
// 	WORD,		/* 231 */
// 	WORD,		/* 232 */
// 	WORD,		/* 233 */
// 	WORD,		/* 234 */
// 	WORD,		/* 235 */
// 	WORD,		/* 236 */
// 	WORD,		/* 237 */
// 	WORD,		/* 238 */
// 	WORD,		/* 239 */
// 	WORD,		/* 240 */
// 	WORD,		/* 241 */
// 	WORD,		/* 242 */
// 	WORD,		/* 243 */
// 	WORD,		/* 244 */
// 	WORD,		/* 245 */
// 	WORD,		/* 246 */
// 	WORD,		/* 247 */
// 	WORD,		/* 248 */
// 	WORD,		/* 249 */
// 	WORD,		/* 250 */
// 	WORD,		/* 251 */
// 	WORD,		/* 252 */
// 	WORD,		/* 253 */
// 	WORD,		/* 254 */
// 	WORD,		/* 255 */
// };
