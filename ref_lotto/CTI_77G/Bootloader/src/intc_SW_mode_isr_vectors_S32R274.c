/*****************************************************************************/
/* FILE NAME: intc_SW_mode_isr_vectors_S32R274.c COPYRIGHT(c) Freescale 2015 */
/*                                                      All Rights Reserved  */
/* DESCRIPTION: S32R274 ISR vectors for INTC in software vector mode         */
/*              Based on S32R274_Interrupt_sources_Rev3.xlsx                 */
/* USAGE:  For desired vector #, replace "dummy" with ISR name and declare   */
/*         your isr name extern like the example below:                      */
/*                       extern void MyPeripheralISR(void);                  */
/*                                                                           */
/*****************************************************************************/	
/* REV      AUTHOR        DATE        DESCRIPTION OF CHANGE                  */
/* ---   -----------    ----------    ---------------------                  */
/* 1.0	  K Zemskov     22 Sep 2015   Initial version                        */
/*****************************************************************************/
#include "typedefs.h"
/*========================================================================*/
/*		PROTOTYPES					                                 	  */
/*========================================================================*/
void dummy 						  (void);

/*========================================================================*/
/*	GLOBAL VARIABLES						                              */
/*========================================================================*/

const uint32_t __attribute__ ((section (".intc_vector_table"))) IntcIsrVectorTable[] = {
    
(uint32_t) &dummy, /* Vector #   0 Software setable flag 0	Software */
(uint32_t) &dummy, /* Vector #   1 Software setable flag 1	Software */
(uint32_t) &dummy, /* Vector #   2 Software setable flag 2	Software */
(uint32_t) &dummy, /* Vector #   3 Software setable flag 3	Software */
(uint32_t) &dummy, /* Vector #   4 Software setable flag 4	Software */
(uint32_t) &dummy, /* Vector #   5 Software setable flag 5	Software */
(uint32_t) &dummy, /* Vector #   6 Software setable flag 6	Software */
(uint32_t) &dummy, /* Vector #   7 Software setable flag 7	Software */
(uint32_t) &dummy, /* Vector #   8 Software setable flag 8	Software */
(uint32_t) &dummy, /* Vector #   9 Software setable flag 9	Software */
(uint32_t) &dummy, /* Vector #  10 Software setable flag 10	Software */
(uint32_t) &dummy, /* Vector #  11 Software setable flag 11	Software */
(uint32_t) &dummy, /* Vector #  12 Software setable flag 12	Software */
(uint32_t) &dummy, /* Vector #  13 Software setable flag 13	Software */
(uint32_t) &dummy, /* Vector #  14 Software setable flag 14	Software */
(uint32_t) &dummy, /* Vector #  15 Software setable flag 15	Software */
(uint32_t) &dummy, /* Vector #  16 */
(uint32_t) &dummy, /* Vector #  17 */
(uint32_t) &dummy, /* Vector #  18 */
(uint32_t) &dummy, /* Vector #  19 */
(uint32_t) &dummy, /* Vector #  20 */
(uint32_t) &dummy, /* Vector #  21 */
(uint32_t) &dummy, /* Vector #  22 */
(uint32_t) &dummy, /* Vector #  23 */
(uint32_t) &dummy, /* Vector #  24 */
(uint32_t) &dummy, /* Vector #  25 */
(uint32_t) &dummy, /* Vector #  26 */
(uint32_t) &dummy, /* Vector #  27 */
(uint32_t) &dummy, /* Vector #  28 */
(uint32_t) &dummy, /* Vector #  29 */
(uint32_t) &dummy, /* Vector #  30 */
(uint32_t) &dummy, /* Vector #  31 */
(uint32_t) &dummy, /* Vector #  32 Timeout	Software Watchdog (SWT_0) */
(uint32_t) &dummy, /* Vector #  33 Timeout	Software Watchdog (SWT_1) */
(uint32_t) &dummy, /* Vector #  34 Timeout	Software Watchdog (SWT_2) */
(uint32_t) &dummy, /* Vector #  35 */
(uint32_t) &dummy, /* Vector #  36 Channel 0	STM_0 */
(uint32_t) &dummy, /* Vector #  37 Channel 1	STM_0 */
(uint32_t) &dummy, /* Vector #  38 Channel 2	STM_0 */
(uint32_t) &dummy, /* Vector #  39 Channel 3	STM_0 */
(uint32_t) &dummy, /* Vector #  40 Channel 0	STM_1 */
(uint32_t) &dummy, /* Vector #  41 Channel 1	STM_1 */
(uint32_t) &dummy, /* Vector #  42 Channel 2	STM_1 */
(uint32_t) &dummy, /* Vector #  43 Channel 3	STM_1 */
(uint32_t) &dummy, /* Vector #  44 Channel 0	STM_2 */
(uint32_t) &dummy, /* Vector #  45 Channel 1	STM_2 */
(uint32_t) &dummy, /* Vector #  46 Channel 2	STM_2 */
(uint32_t) &dummy, /* Vector #  47 Channel 3	STM_2 */
(uint32_t) &dummy, /* Vector #  48 */
(uint32_t) &dummy, /* Vector #  49 */
(uint32_t) &dummy, /* Vector #  50 */
(uint32_t) &dummy, /* Vector #  51 */
(uint32_t) &dummy, /* Vector #  52 Combined Error	eDMA */
(uint32_t) &dummy, /* Vector #  53 Channel 0	eDMA */
(uint32_t) &dummy, /* Vector #  54 Channel 1	eDMA */
(uint32_t) &dummy, /* Vector #  55 Channel 2	eDMA */
(uint32_t) &dummy, /* Vector #  56 Channel 3	eDMA */
(uint32_t) &dummy, /* Vector #  57 Channel 4	eDMA */
(uint32_t) &dummy, /* Vector #  58 Channel 5	eDMA */
(uint32_t) &dummy, /* Vector #  59 Channel 6	eDMA */
(uint32_t) &dummy, /* Vector #  60 Channel 7	eDMA */
(uint32_t) &dummy, /* Vector #  61 Channel 8	eDMA */
(uint32_t) &dummy, /* Vector #  62 Channel 9	eDMA */
(uint32_t) &dummy, /* Vector #  63 Channel 10	eDMA */
(uint32_t) &dummy, /* Vector #  64 Channel 11	eDMA */
(uint32_t) &dummy, /* Vector #  65 Channel 12	eDMA */
(uint32_t) &dummy, /* Vector #  66 Channel 13	eDMA */
(uint32_t) &dummy, /* Vector #  67 Channel 14	eDMA */
(uint32_t) &dummy, /* Vector #  68 Channel 15	eDMA */
(uint32_t) &dummy, /* Vector #  69 Channel 16	eDMA */
(uint32_t) &dummy, /* Vector #  70 Channel 17	eDMA */
(uint32_t) &dummy, /* Vector #  71 Channel 18	eDMA */
(uint32_t) &dummy, /* Vector #  72 Channel 19	eDMA */
(uint32_t) &dummy, /* Vector #  73 Channel 20	eDMA */
(uint32_t) &dummy, /* Vector #  74 Channel 21	eDMA */
(uint32_t) &dummy, /* Vector #  75 Channel 22	eDMA */
(uint32_t) &dummy, /* Vector #  76 Channel 23	eDMA */
(uint32_t) &dummy, /* Vector #  77 Channel 24	eDMA */
(uint32_t) &dummy, /* Vector #  78 Channel 25	eDMA */
(uint32_t) &dummy, /* Vector #  79 Channel 26	eDMA */
(uint32_t) &dummy, /* Vector #  80 Channel 27	eDMA */
(uint32_t) &dummy, /* Vector #  81 Channel 28	eDMA */
(uint32_t) &dummy, /* Vector #  82 Channel 29	eDMA */
(uint32_t) &dummy, /* Vector #  83 Channel 30	eDMA */
(uint32_t) &dummy, /* Vector #  84 Channel 31	eDMA */
(uint32_t) &dummy, /* Vector #  85 */
(uint32_t) &dummy, /* Vector #  86 */
(uint32_t) &dummy, /* Vector #  87 */
(uint32_t) &dummy, /* Vector #  88 */
(uint32_t) &dummy, /* Vector #  89 */
(uint32_t) &dummy, /* Vector #  90 */
(uint32_t) &dummy, /* Vector #  91 */
(uint32_t) &dummy, /* Vector #  92 */
(uint32_t) &dummy, /* Vector #  93 */
(uint32_t) &dummy, /* Vector #  94 */
(uint32_t) &dummy, /* Vector #  95 */
(uint32_t) &dummy, /* Vector #  96 */
(uint32_t) &dummy, /* Vector #  97 */
(uint32_t) &dummy, /* Vector #  98 */
(uint32_t) &dummy, /* Vector #  99 */
(uint32_t) &dummy, /* Vector # 100 */

(uint32_t) &dummy, /* Vector # 101 */
(uint32_t) &dummy, /* Vector # 102 */
(uint32_t) &dummy, /* Vector # 103 */
(uint32_t) &dummy, /* Vector # 104 */
(uint32_t) &dummy, /* Vector # 105 */
(uint32_t) &dummy, /* Vector # 106 */
(uint32_t) &dummy, /* Vector # 107 */
(uint32_t) &dummy, /* Vector # 108 */
(uint32_t) &dummy, /* Vector # 109 */
(uint32_t) &dummy, /* Vector # 110 */
(uint32_t) &dummy, /* Vector # 111 */
(uint32_t) &dummy, /* Vector # 112 */
(uint32_t) &dummy, /* Vector # 113 */
(uint32_t) &dummy, /* Vector # 114 */
(uint32_t) &dummy, /* Vector # 115 */
(uint32_t) &dummy, /* Vector # 116 */
(uint32_t) &dummy, /* Vector # 117 */
(uint32_t) &dummy, /* Vector # 118 */
(uint32_t) &dummy, /* Vector # 119 */
(uint32_t) &dummy, /* Vector # 120 */
(uint32_t) &dummy, /* Vector # 121 */
(uint32_t) &dummy, /* Vector # 122 */
(uint32_t) &dummy, /* Vector # 123 */
(uint32_t) &dummy, /* Vector # 124 */
(uint32_t) &dummy, /* Vector # 125 */
(uint32_t) &dummy, /* Vector # 126 */
(uint32_t) &dummy, /* Vector # 127 */
(uint32_t) &dummy, /* Vector # 128 */
(uint32_t) &dummy, /* Vector # 129 */
(uint32_t) &dummy, /* Vector # 130 */
(uint32_t) &dummy, /* Vector # 131 */
(uint32_t) &dummy, /* Vector # 132 */
(uint32_t) &dummy, /* Vector # 133 */
(uint32_t) &dummy, /* Vector # 134 */
(uint32_t) &dummy, /* Vector # 135 */
(uint32_t) &dummy, /* Vector # 136 */
(uint32_t) &dummy, /* Vector # 137 */
(uint32_t) &dummy, /* Vector # 138 */
(uint32_t) &dummy, /* Vector # 139 */
(uint32_t) &dummy, /* Vector # 140 */
(uint32_t) &dummy, /* Vector # 141 */
(uint32_t) &dummy, /* Vector # 142 */
(uint32_t) &dummy, /* Vector # 143 */
(uint32_t) &dummy, /* Vector # 144 */
(uint32_t) &dummy, /* Vector # 145 */
(uint32_t) &dummy, /* Vector # 146 */
(uint32_t) &dummy, /* Vector # 147 */
(uint32_t) &dummy, /* Vector # 148 */
(uint32_t) &dummy, /* Vector # 149 */
(uint32_t) &dummy, /* Vector # 150 */
(uint32_t) &dummy, /* Vector # 151 */
(uint32_t) &dummy, /* Vector # 152 */
(uint32_t) &dummy, /* Vector # 153 */
(uint32_t) &dummy, /* Vector # 154 */
(uint32_t) &dummy, /* Vector # 155 */
(uint32_t) &dummy, /* Vector # 156 */
(uint32_t) &dummy, /* Vector # 157 */
(uint32_t) &dummy, /* Vector # 158 */
(uint32_t) &dummy, /* Vector # 159 */
(uint32_t) &dummy, /* Vector # 160 */
(uint32_t) &dummy, /* Vector # 161 */
(uint32_t) &dummy, /* Vector # 162 */
(uint32_t) &dummy, /* Vector # 163 */
(uint32_t) &dummy, /* Vector # 164 */
(uint32_t) &dummy, /* Vector # 165 */
(uint32_t) &dummy, /* Vector # 166 */
(uint32_t) &dummy, /* Vector # 167 */
(uint32_t) &dummy, /* Vector # 168 */
(uint32_t) &dummy, /* Vector # 169 */
(uint32_t) &dummy, /* Vector # 170 */
(uint32_t) &dummy, /* Vector # 171 */
(uint32_t) &dummy, /* Vector # 172 */
(uint32_t) &dummy, /* Vector # 173 */
(uint32_t) &dummy, /* Vector # 174 */
(uint32_t) &dummy, /* Vector # 175 */
(uint32_t) &dummy, /* Vector # 176 */
(uint32_t) &dummy, /* Vector # 177 */
(uint32_t) &dummy, /* Vector # 178 */
(uint32_t) &dummy, /* Vector # 179 */
(uint32_t) &dummy, /* Vector # 180 */
(uint32_t) &dummy, /* Vector # 181 */
(uint32_t) &dummy, /* Vector # 182 */
(uint32_t) &dummy, /* Vector # 183 */
(uint32_t) &dummy, /* Vector # 184 */
(uint32_t) &dummy, /* Vector # 185 Prog/Erase/Suspend IRQ	Pflash  */
(uint32_t) &dummy, /* Vector # 186 */
(uint32_t) &dummy, /* Vector # 187 */
(uint32_t) &dummy, /* Vector # 188 */
(uint32_t) &dummy, /* Vector # 189 */
(uint32_t) &dummy, /* Vector # 190 */
(uint32_t) &dummy, /* Vector # 191 */
(uint32_t) &dummy, /* Vector # 192 */
(uint32_t) &dummy, /* Vector # 193 */
(uint32_t) &dummy, /* Vector # 194 */
(uint32_t) &dummy, /* Vector # 195 */
(uint32_t) &dummy, /* Vector # 196 */
(uint32_t) &dummy, /* Vector # 197 */
(uint32_t) &dummy, /* Vector # 198 */
(uint32_t) &dummy, /* Vector # 199 */
(uint32_t) &dummy, /* Vector # 200 */

(uint32_t) &dummy, /* Vector # 201 */
(uint32_t) &dummy, /* Vector # 202 */
(uint32_t) &dummy, /* Vector # 203 */
(uint32_t) &dummy, /* Vector # 204 */
(uint32_t) &dummy, /* Vector # 205 */
(uint32_t) &dummy, /* Vector # 206 */
(uint32_t) &dummy, /* Vector # 207 */
(uint32_t) &dummy, /* Vector # 208 */
(uint32_t) &dummy, /* Vector # 209 */
(uint32_t) &dummy, /* Vector # 210 */
(uint32_t) &dummy, /* Vector # 211 */
(uint32_t) &dummy, /* Vector # 212 */
(uint32_t) &dummy, /* Vector # 213 */
(uint32_t) &dummy, /* Vector # 214 */
(uint32_t) &dummy, /* Vector # 215 */
(uint32_t) &dummy, /* Vector # 216 TS_TIMER | TS_AVAIL	ENET_0 */
(uint32_t) &dummy, /* Vector # 217 TX_BUFFER |TX_FRAME	ENET_0 */
(uint32_t) &dummy, /* Vector # 218 RX_BUFFER |RX_FRAME	ENET_0 */
(uint32_t) &dummy, /* Vector # 219 "WAKE_SYNC | WAKE_ASYNC | */
                   /*              RX_ERR | TX_UNDER | */
		           /*              COLL_RETRY | COLL_LATE | */
		           /*              BUS_ERR | XFR_DONE	| */
		           /*              GRA_STOP | TX_BABB | RX_BABB"	ENET_0  */
(uint32_t) &dummy, /* Vector # 220 "TIMER_SYNC | TIMER_ASYNC"	ENET_0 */
(uint32_t) &dummy, /* Vector # 221 */
(uint32_t) &dummy, /* Vector # 222 */
(uint32_t) &dummy, /* Vector # 223 */
(uint32_t) &dummy, /* Vector # 224 */
(uint32_t) &dummy, /* Vector # 225 */
(uint32_t) &dummy, /* Vector # 226 Channel 0	PIT_0 */
(uint32_t) &dummy, /* Vector # 227 Channel 1	PIT_0 */
(uint32_t) &dummy, /* Vector # 228 Channel 2	PIT_0 */
(uint32_t) &dummy, /* Vector # 229 Channel 3	PIT_0 */
(uint32_t) &dummy, /* Vector # 230 Channel 0	PIT_1 */
(uint32_t) &dummy, /* Vector # 231 Channel 1	PIT_1 */
(uint32_t) &dummy, /* Vector # 232 Channel 2	PIT_1 */
(uint32_t) &dummy, /* Vector # 233 Channel 3	PIT_1 */
(uint32_t) &dummy, /* Vector # 234 */
(uint32_t) &dummy, /* Vector # 235 */
(uint32_t) &dummy, /* Vector # 236 */
(uint32_t) &dummy, /* Vector # 237 */
(uint32_t) &dummy, /* Vector # 238 */
(uint32_t) &dummy, /* Vector # 239 */
(uint32_t) &dummy, /* Vector # 240 */
(uint32_t) &dummy, /* Vector # 241 */
(uint32_t) &dummy, /* Vector # 242 */
(uint32_t) &dummy, /* Vector # 243 SIUL2 External IRQ_0	System Integration Unit Lite (SIUL2) */
(uint32_t) &dummy, /* Vector # 244 SIUL2 External IRQ_1	System Integration Unit Lite (SIUL2) */
(uint32_t) &dummy, /* Vector # 245 SIUL2 External IRQ_2	System Integration Unit Lite (SIUL2) */
(uint32_t) &dummy, /* Vector # 246 SIUL2 External IRQ_3	System Integration Unit Lite (SIUL2) */
(uint32_t) &dummy, /* Vector # 247 */
(uint32_t) &dummy, /* Vector # 248 */
(uint32_t) &dummy, /* Vector # 249 */
(uint32_t) &dummy, /* Vector # 250 */
(uint32_t) &dummy, /* Vector # 251 Safe Mode Interrupt	MC_ME */
(uint32_t) &dummy, /* Vector # 252 Mode Transition Interrupt	MC_ME */
(uint32_t) &dummy, /* Vector # 253 Invalid Mode Interrupt	MC_ME */
(uint32_t) &dummy, /* Vector # 254 Invalid Mode Config Interrupt	MC_ME */
(uint32_t) &dummy, /* Vector # 255 Alternate Event	MC_ME */
(uint32_t) &dummy, /* Vector # 256 */
(uint32_t) &dummy, /* Vector # 257 */
(uint32_t) &dummy, /* Vector # 258 */
(uint32_t) &dummy, /* Vector # 259 */
(uint32_t) &dummy, /* Vector # 260 */
(uint32_t) &dummy, /* Vector # 261 */
(uint32_t) &dummy, /* Vector # 262 */
(uint32_t) &dummy, /* Vector # 263 */
(uint32_t) &dummy, /* Vector # 264 */
(uint32_t) &dummy, /* Vector # 265 */
(uint32_t) &dummy, /* Vector # 266 */
(uint32_t) &dummy, /* Vector # 267 */
(uint32_t) &dummy, /* Vector # 268 SPI_SR[TFUF]	SPI_1 */
				   /*              SPI_SR[RFOF] */
				   /*              SPI_SR[SPEF] */
(uint32_t) &dummy, /* Vector # 269 SPI_SR[EOQF]	SPI_1 */
(uint32_t) &dummy, /* Vector # 270 SPI_SR[TFFF]	SPI_1 */
(uint32_t) &dummy, /* Vector # 271 SPI_SR[TCF]	SPI_1 */
(uint32_t) &dummy, /* Vector # 272 SPI_SR[RFDF]	SPI_1 */
(uint32_t) &dummy, /* Vector # 273 */
(uint32_t) &dummy, /* Vector # 274 */
(uint32_t) &dummy, /* Vector # 275 */
(uint32_t) &dummy, /* Vector # 276 */
(uint32_t) &dummy, /* Vector # 277 SPI_SR[TFUF]	SPI_2 */
				   /*              SPI_SR[RFOF] */
				   /*              SPI_SR[SPEF] */
(uint32_t) &dummy, /* Vector # 278 SPI_SR[EOQF]	SPI_2 */
(uint32_t) &dummy, /* Vector # 279 SPI_SR[TFFF]	SPI_2 */
(uint32_t) &dummy, /* Vector # 280 SPI_SR[TCF]	SPI_2 */
(uint32_t) &dummy, /* Vector # 281 SPI_SR[RFDF]	SPI_2 */
(uint32_t) &dummy, /* Vector # 282 */
(uint32_t) &dummy, /* Vector # 283 */
(uint32_t) &dummy, /* Vector # 284 */
(uint32_t) &dummy, /* Vector # 285 */
(uint32_t) &dummy, /* Vector # 286 */
(uint32_t) &dummy, /* Vector # 287 */
(uint32_t) &dummy, /* Vector # 288 */
(uint32_t) &dummy, /* Vector # 289 */
(uint32_t) &dummy, /* Vector # 290 */
(uint32_t) &dummy, /* Vector # 291 */
(uint32_t) &dummy, /* Vector # 292 */
(uint32_t) &dummy, /* Vector # 293 */
(uint32_t) &dummy, /* Vector # 294 */
(uint32_t) &dummy, /* Vector # 295 */
(uint32_t) &dummy, /* Vector # 296 */
(uint32_t) &dummy, /* Vector # 297 */
(uint32_t) &dummy, /* Vector # 298 */
(uint32_t) &dummy, /* Vector # 299 */
(uint32_t) &dummy, /* Vector # 300 */

(uint32_t) &dummy, /* Vector # 301 */
(uint32_t) &dummy, /* Vector # 302 */
(uint32_t) &dummy, /* Vector # 303 */
(uint32_t) &dummy, /* Vector # 304 */
(uint32_t) &dummy, /* Vector # 305 */
(uint32_t) &dummy, /* Vector # 306 */
(uint32_t) &dummy, /* Vector # 307 */
(uint32_t) &dummy, /* Vector # 308 */
(uint32_t) &dummy, /* Vector # 309 */
(uint32_t) &dummy, /* Vector # 310 */
(uint32_t) &dummy, /* Vector # 311 */
(uint32_t) &dummy, /* Vector # 312 */
(uint32_t) &dummy, /* Vector # 313 */
(uint32_t) &dummy, /* Vector # 314 */
(uint32_t) &dummy, /* Vector # 315 */
(uint32_t) &dummy, /* Vector # 316 */
(uint32_t) &dummy, /* Vector # 317 */
(uint32_t) &dummy, /* Vector # 318 */
(uint32_t) &dummy, /* Vector # 319 */
(uint32_t) &dummy, /* Vector # 320 */
(uint32_t) &dummy, /* Vector # 321 */
(uint32_t) &dummy, /* Vector # 322 */
(uint32_t) &dummy, /* Vector # 323 */
(uint32_t) &dummy, /* Vector # 324 */
(uint32_t) &dummy, /* Vector # 325 */
(uint32_t) &dummy, /* Vector # 326 */
(uint32_t) &dummy, /* Vector # 327 */
(uint32_t) &dummy, /* Vector # 328 */
(uint32_t) &dummy, /* Vector # 329 */
(uint32_t) &dummy, /* Vector # 330 */
(uint32_t) &dummy, /* Vector # 331 */
(uint32_t) &dummy, /* Vector # 332 */
(uint32_t) &dummy, /* Vector # 333 */
(uint32_t) &dummy, /* Vector # 334 */
(uint32_t) &dummy, /* Vector # 335 */
(uint32_t) &dummy, /* Vector # 336 */
(uint32_t) &dummy, /* Vector # 337 */
(uint32_t) &dummy, /* Vector # 338 */
(uint32_t) &dummy, /* Vector # 339 */
(uint32_t) &dummy, /* Vector # 340 */
(uint32_t) &dummy, /* Vector # 341 */
(uint32_t) &dummy, /* Vector # 342 */
(uint32_t) &dummy, /* Vector # 343 */
(uint32_t) &dummy, /* Vector # 344 */
(uint32_t) &dummy, /* Vector # 345 */
(uint32_t) &dummy, /* Vector # 346 */
(uint32_t) &dummy, /* Vector # 347 */
(uint32_t) &dummy, /* Vector # 348 */
(uint32_t) &dummy, /* Vector # 349 */
(uint32_t) &dummy, /* Vector # 350 */
(uint32_t) &dummy, /* Vector # 351 */
(uint32_t) &dummy, /* Vector # 352 */
(uint32_t) &dummy, /* Vector # 353 */
(uint32_t) &dummy, /* Vector # 354 */
(uint32_t) &dummy, /* Vector # 355 */
(uint32_t) &dummy, /* Vector # 356 */
(uint32_t) &dummy, /* Vector # 357 */
(uint32_t) &dummy, /* Vector # 358 */
(uint32_t) &dummy, /* Vector # 359 */
(uint32_t) &dummy, /* Vector # 360 */
(uint32_t) &dummy, /* Vector # 361 */
(uint32_t) &dummy, /* Vector # 362 */
(uint32_t) &dummy, /* Vector # 363 */
(uint32_t) &dummy, /* Vector # 364 */
(uint32_t) &dummy, /* Vector # 365 */
(uint32_t) &dummy, /* Vector # 366 */
(uint32_t) &dummy, /* Vector # 367 */
(uint32_t) &dummy, /* Vector # 368 */
(uint32_t) &dummy, /* Vector # 369 */
(uint32_t) &dummy, /* Vector # 370 */
(uint32_t) &dummy, /* Vector # 371 */
(uint32_t) &dummy, /* Vector # 372 */
(uint32_t) &dummy, /* Vector # 373 */
(uint32_t) &dummy, /* Vector # 374 */
(uint32_t) &dummy, /* Vector # 375 */
(uint32_t) &dummy, /* Vector # 376 */
(uint32_t) &dummy, /* Vector # 377 */
(uint32_t) &dummy, /* Vector # 378 */
(uint32_t) &dummy, /* Vector # 379 */
(uint32_t) &dummy, /* Vector # 380 LINFlex_RXI	LINFlex_1 */
(uint32_t) &dummy, /* Vector # 381 LINFlex_TXI	LINFlex_1 */
(uint32_t) &dummy, /* Vector # 382 LINFlex_ERR	LINFlex_1 */
(uint32_t) &dummy, /* Vector # 383 */
(uint32_t) &dummy, /* Vector # 384 */
(uint32_t) &dummy, /* Vector # 385 */
(uint32_t) &dummy, /* Vector # 386 */
(uint32_t) &dummy, /* Vector # 387 */
(uint32_t) &dummy, /* Vector # 388 */
(uint32_t) &dummy, /* Vector # 389 */
(uint32_t) &dummy, /* Vector # 390 */
(uint32_t) &dummy, /* Vector # 391 */
(uint32_t) &dummy, /* Vector # 392 */
(uint32_t) &dummy, /* Vector # 393 */
(uint32_t) &dummy, /* Vector # 394 */
(uint32_t) &dummy, /* Vector # 395 */
(uint32_t) &dummy, /* Vector # 396 */
(uint32_t) &dummy, /* Vector # 397 */
(uint32_t) &dummy, /* Vector # 398 */
(uint32_t) &dummy, /* Vector # 399 */
(uint32_t) &dummy, /* Vector # 400 */

(uint32_t) &dummy, /* Vector # 401 */
(uint32_t) &dummy, /* Vector # 402 */
(uint32_t) &dummy, /* Vector # 403 */
(uint32_t) &dummy, /* Vector # 404 */
(uint32_t) &dummy, /* Vector # 405 */
(uint32_t) &dummy, /* Vector # 406 */
(uint32_t) &dummy, /* Vector # 407 */
(uint32_t) &dummy, /* Vector # 408 */
(uint32_t) &dummy, /* Vector # 409 */
(uint32_t) &dummy, /* Vector # 410 */
(uint32_t) &dummy, /* Vector # 411 */
(uint32_t) &dummy, /* Vector # 412 */
(uint32_t) &dummy, /* Vector # 413 */
(uint32_t) &dummy, /* Vector # 414 */
(uint32_t) &dummy, /* Vector # 415 */
(uint32_t) &dummy, /* Vector # 416 */
(uint32_t) &dummy, /* Vector # 417 */
(uint32_t) &dummy, /* Vector # 418 */
(uint32_t) &dummy, /* Vector # 419 */
(uint32_t) &dummy, /* Vector # 420 */
(uint32_t) &dummy, /* Vector # 421 */
(uint32_t) &dummy, /* Vector # 422 */
(uint32_t) &dummy, /* Vector # 423 */
(uint32_t) &dummy, /* Vector # 424 */
(uint32_t) &dummy, /* Vector # 425 */
(uint32_t) &dummy, /* Vector # 426 */
(uint32_t) &dummy, /* Vector # 427 */
(uint32_t) &dummy, /* Vector # 428 */
(uint32_t) &dummy, /* Vector # 429 */
(uint32_t) &dummy, /* Vector # 430 */
(uint32_t) &dummy, /* Vector # 431 */
(uint32_t) &dummy, /* Vector # 432 */
(uint32_t) &dummy, /* Vector # 433 */
(uint32_t) &dummy, /* Vector # 434 */
(uint32_t) &dummy, /* Vector # 435 */
(uint32_t) &dummy, /* Vector # 436 */
(uint32_t) &dummy, /* Vector # 437 */
(uint32_t) &dummy, /* Vector # 438 */
(uint32_t) &dummy, /* Vector # 439 */
(uint32_t) &dummy, /* Vector # 440 */
(uint32_t) &dummy, /* Vector # 441 */
(uint32_t) &dummy, /* Vector # 442 IRQ_0	IIC_1 */
(uint32_t) &dummy, /* Vector # 443 */
(uint32_t) &dummy, /* Vector # 444 IRQ_0	IIC_2 */
(uint32_t) &dummy, /* Vector # 445 */
(uint32_t) &dummy, /* Vector # 446 */
(uint32_t) &dummy, /* Vector # 447 */
(uint32_t) &dummy, /* Vector # 448 */
(uint32_t) &dummy, /* Vector # 449 */
(uint32_t) &dummy, /* Vector # 450 */
(uint32_t) &dummy, /* Vector # 451 */
(uint32_t) &dummy, /* Vector # 452 */
(uint32_t) &dummy, /* Vector # 453 LRNEIF | DRNEIF	FLEXRAY_0 */
(uint32_t) &dummy, /* Vector # 454 LRCEIF | DRCEIF	FLEXRAY_0 */
(uint32_t) &dummy, /* Vector # 455 FNEAIF	FLEXRAY_0 */
(uint32_t) &dummy, /* Vector # 456 FNEBIF	FLEXRAY_0 */
(uint32_t) &dummy, /* Vector # 457 WUPIF	FLEXRAY_0 */
(uint32_t) &dummy, /* Vector # 458 PRIF	FLEXRAY_0 */
(uint32_t) &dummy, /* Vector # 459 CHIF	FLEXRAY_0 */
(uint32_t) &dummy, /* Vector # 460 TBIF	FLEXRAY_0 */
(uint32_t) &dummy, /* Vector # 461 RBIF	FLEXRAY_0 */
(uint32_t) &dummy, /* Vector # 462 MIF	FLEXRAY_0 */
(uint32_t) &dummy, /* Vector # 463 */
(uint32_t) &dummy, /* Vector # 464 */
(uint32_t) &dummy, /* Vector # 465 */
(uint32_t) &dummy, /* Vector # 466 */
(uint32_t) &dummy, /* Vector # 467 */
(uint32_t) &dummy, /* Vector # 468 */
(uint32_t) &dummy, /* Vector # 469 */
(uint32_t) &dummy, /* Vector # 470 */
(uint32_t) &dummy, /* Vector # 471 */
(uint32_t) &dummy, /* Vector # 472 */
(uint32_t) &dummy, /* Vector # 473 */
(uint32_t) &dummy, /* Vector # 474 */
(uint32_t) &dummy, /* Vector # 475 */
(uint32_t) &dummy, /* Vector # 476 */
(uint32_t) &dummy, /* Vector # 477 Power Management Controller	PMC */
(uint32_t) &dummy, /* Vector # 478 Temperature Sensor	PMC */
(uint32_t) &dummy, /* Vector # 479 */
(uint32_t) &dummy, /* Vector # 480 */
(uint32_t) &dummy, /* Vector # 481 */
(uint32_t) &dummy, /* Vector # 482 */
(uint32_t) &dummy, /* Vector # 483 */
(uint32_t) &dummy, /* Vector # 484 */
(uint32_t) &dummy, /* Vector # 485 */
(uint32_t) &dummy, /* Vector # 486 */
(uint32_t) &dummy, /* Vector # 487 */
(uint32_t) &dummy, /* Vector # 488 irq_alarm_b	FCCU */
(uint32_t) &dummy, /* Vector # 489 irq_misc_b	FCCU */
(uint32_t) &dummy, /* Vector # 490 */
(uint32_t) &dummy, /* Vector # 491 */
(uint32_t) &dummy, /* Vector # 492 */
(uint32_t) &dummy, /* Vector # 493 */
(uint32_t) &dummy, /* Vector # 494 */
(uint32_t) &dummy, /* Vector # 495 */
(uint32_t) &dummy, /* Vector # 496 ADC_EOC	ADC_0 */
(uint32_t) &dummy, /* Vector # 497 ADC_ER	ADC_0 */
(uint32_t) &dummy, /* Vector # 498 ADC_WD	ADC_0 */
(uint32_t) &dummy, /* Vector # 499 */
(uint32_t) &dummy, /* Vector # 500 ADC_EOC	ADC_1 */

(uint32_t) &dummy, /* Vector # 501 ADC_ER	ADC_1 */
(uint32_t) &dummy, /* Vector # 502 ADC_WD	ADC_1 */
(uint32_t) &dummy, /* Vector # 503 */
(uint32_t) &dummy, /* Vector # 504 */
(uint32_t) &dummy, /* Vector # 505 */
(uint32_t) &dummy, /* Vector # 506 */
(uint32_t) &dummy, /* Vector # 507 */
(uint32_t) &dummy, /* Vector # 508 */
(uint32_t) &dummy, /* Vector # 509 */
(uint32_t) &dummy, /* Vector # 510 */
(uint32_t) &dummy, /* Vector # 511 */
(uint32_t) &dummy, /* Vector # 512 */
(uint32_t) &dummy, /* Vector # 513 */
(uint32_t) &dummy, /* Vector # 514 */
(uint32_t) &dummy, /* Vector # 515 */
(uint32_t) &dummy, /* Vector # 516 */
(uint32_t) &dummy, /* Vector # 517 */
(uint32_t) &dummy, /* Vector # 518 */
(uint32_t) &dummy, /* Vector # 519 */
(uint32_t) &dummy, /* Vector # 520 FLEXCAN_ESR[ERR_INT]	FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 521 FLEXCAN_ESR_BOFF | FLEXCAN_Transmit_Warning | FLEXCAN_Receive_Warning	FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 522 FLEXCAN_BUF_00_03	FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 523 FLEXCAN_BUF_04_07	FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 524 FLEXCAN_BUF_08_11	FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 525 FLEXCAN_BUF_12_15	FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 526 FLEXCAN_BUF_16_31	FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 527 FLEXCAN_BUF_32_39	FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 528 FLEXCAN_BUF_40_47	FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 529 FLEXCAN_BUF_48_55	FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 530 FLEXCAN_BUF_56_63	FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 531 FLEXCAN_BUF_64_79	FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 532 FLEXCAN_BUF_80_95	FlexCAN_0 */
(uint32_t) &dummy, /* Vector # 533 FLEXCAN_ESR[ERR_INT]	FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 534 FLEXCAN_ESR_BOFF | FLEXCAN_Transmit_Warning | FLEXCAN_Receive_Warning	FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 535 FLEXCAN_BUF_00_03	FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 536 FLEXCAN_BUF_04_07	FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 537 FLEXCAN_BUF_08_11	FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 538 FLEXCAN_BUF_12_15	FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 539 FLEXCAN_BUF_16_31	FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 540 FLEXCAN_BUF_32_39	FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 541 FLEXCAN_BUF_40_47	FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 542 FLEXCAN_BUF_48_55	FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 543 FLEXCAN_BUF_56_63	FlexCAN_1 */
(uint32_t) &dummy, /* Vector # 544 */
(uint32_t) &dummy, /* Vector # 545 */
(uint32_t) &dummy, /* Vector # 546 FLEXCAN_ESR[ERR_INT]	FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 547 FLEXCAN_ESR_BOFF | FLEXCAN_Transmit_Warning | FLEXCAN_Receive_Warning	FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 548 FLEXCAN_BUF_00_03	FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 549 FLEXCAN_BUF_04_07	FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 550 FLEXCAN_BUF_08_11	FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 551 FLEXCAN_BUF_12_15	FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 552 FLEXCAN_BUF_16_31	FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 553 FLEXCAN_BUF_32_39	FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 554 FLEXCAN_BUF_40_47	FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 555 FLEXCAN_BUF_48_55	FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 556 FLEXCAN_BUF_56_63	FlexCAN_2 */
(uint32_t) &dummy, /* Vector # 557 FLEXCAN_BUF_64_79	FlexCan_2 */
(uint32_t) &dummy, /* Vector # 558 FLEXCAN_BUF_80_95	FlexCan_2 */
(uint32_t) &dummy, /* Vector # 559 */
(uint32_t) &dummy, /* Vector # 560 */
(uint32_t) &dummy, /* Vector # 561 */
(uint32_t) &dummy, /* Vector # 562 */
(uint32_t) &dummy, /* Vector # 563 */
(uint32_t) &dummy, /* Vector # 564 */
(uint32_t) &dummy, /* Vector # 565 */
(uint32_t) &dummy, /* Vector # 566 */
(uint32_t) &dummy, /* Vector # 567 */
(uint32_t) &dummy, /* Vector # 568 */
(uint32_t) &dummy, /* Vector # 569 */
(uint32_t) &dummy, /* Vector # 570 */
(uint32_t) &dummy, /* Vector # 571 */
(uint32_t) &dummy, /* Vector # 572 */
(uint32_t) &dummy, /* Vector # 573 */
(uint32_t) &dummy, /* Vector # 574 */
(uint32_t) &dummy, /* Vector # 575 */
(uint32_t) &dummy, /* Vector # 576 */
(uint32_t) &dummy, /* Vector # 577 */
(uint32_t) &dummy, /* Vector # 578 */
(uint32_t) &dummy, /* Vector # 579 */
(uint32_t) &dummy, /* Vector # 580 */
(uint32_t) &dummy, /* Vector # 581 */
(uint32_t) &dummy, /* Vector # 582 */
(uint32_t) &dummy, /* Vector # 583 */
(uint32_t) &dummy, /* Vector # 584 */
(uint32_t) &dummy, /* Vector # 585 */
(uint32_t) &dummy, /* Vector # 586 */
(uint32_t) &dummy, /* Vector # 587 */
(uint32_t) &dummy, /* Vector # 588 */
(uint32_t) &dummy, /* Vector # 589 */
(uint32_t) &dummy, /* Vector # 590 */
(uint32_t) &dummy, /* Vector # 591 */
(uint32_t) &dummy, /* Vector # 592 */
(uint32_t) &dummy, /* Vector # 593 */
(uint32_t) &dummy, /* Vector # 594 Channel 1	SIPI_0 */
(uint32_t) &dummy, /* Vector # 595 Channel 2	SIPI_0 */
(uint32_t) &dummy, /* Vector # 596 Channel 3	SIPI_0 */
(uint32_t) &dummy, /* Vector # 597 Channel 4	SIPI_0 */
(uint32_t) &dummy, /* Vector # 598 */
(uint32_t) &dummy, /* Vector # 599 */
(uint32_t) &dummy, /* Vector # 600 */

(uint32_t) &dummy, /* Vector # 601 */
(uint32_t) &dummy, /* Vector # 602 Error 1	SIPI_0 */
(uint32_t) &dummy, /* Vector # 603 Error 2	SIPI_0 */
(uint32_t) &dummy, /* Vector # 604 Trigger	SIPI_0 */
(uint32_t) &dummy, /* Vector # 605 TX	LFAST_0 */
(uint32_t) &dummy, /* Vector # 606 TX Exception	LFAST_0 */
(uint32_t) &dummy, /* Vector # 607 RX	LFAST_0 */
(uint32_t) &dummy, /* Vector # 608 RX Exception	LFAST_0 */
(uint32_t) &dummy, /* Vector # 609 RX ICLC	LFAST_0 */
(uint32_t) &dummy, /* Vector # 610 */
(uint32_t) &dummy, /* Vector # 611 */
(uint32_t) &dummy, /* Vector # 612 */
(uint32_t) &dummy, /* Vector # 613 */
(uint32_t) &dummy, /* Vector # 614 */
(uint32_t) &dummy, /* Vector # 615 */
(uint32_t) &dummy, /* Vector # 616 */
(uint32_t) &dummy, /* Vector # 617 */
(uint32_t) &dummy, /* Vector # 618 */
(uint32_t) &dummy, /* Vector # 619 */
(uint32_t) &dummy, /* Vector # 620 */
(uint32_t) &dummy, /* Vector # 621 */
(uint32_t) &dummy, /* Vector # 622 TC0IR	ETIMER_1 */
(uint32_t) &dummy, /* Vector # 623 TC1IR	ETIMER_1 */
(uint32_t) &dummy, /* Vector # 624 TC2IR	ETIMER_1 */
(uint32_t) &dummy, /* Vector # 625 TC3IR	ETIMER_1 */
(uint32_t) &dummy, /* Vector # 626 TC4IR	ETIMER_1 */
(uint32_t) &dummy, /* Vector # 627 TC5IR	ETIMER_1 */
(uint32_t) &dummy, /* Vector # 628 TC6IR	ETIMER_1 */
(uint32_t) &dummy, /* Vector # 629 */
(uint32_t) &dummy, /* Vector # 630 */
(uint32_t) &dummy, /* Vector # 631 */
(uint32_t) &dummy, /* Vector # 632 RCF	ETIMER_1 */
(uint32_t) &dummy, /* Vector # 633 TC0IR	ETIMER_2 */
(uint32_t) &dummy, /* Vector # 634 TC1IR	ETIMER_2 */
(uint32_t) &dummy, /* Vector # 635 TC2IR	ETIMER_2 */
(uint32_t) &dummy, /* Vector # 636 TC3IR	ETIMER_2 */
(uint32_t) &dummy, /* Vector # 637 TC4IR	ETIMER_2 */
(uint32_t) &dummy, /* Vector # 638 TC5IR	ETIMER_2 */
(uint32_t) &dummy, /* Vector # 639 TC6IR	ETIMER_2 */
(uint32_t) &dummy, /* Vector # 640 TC7IR	ETIMER_2 */
(uint32_t) &dummy, /* Vector # 641 */
(uint32_t) &dummy, /* Vector # 642 */
(uint32_t) &dummy, /* Vector # 643 RCF	ETIMER_2 */
(uint32_t) &dummy, /* Vector # 644 */
(uint32_t) &dummy, /* Vector # 645 */
(uint32_t) &dummy, /* Vector # 646 */
(uint32_t) &dummy, /* Vector # 647 */
(uint32_t) &dummy, /* Vector # 648 */
(uint32_t) &dummy, /* Vector # 649 */
(uint32_t) &dummy, /* Vector # 650 */
(uint32_t) &dummy, /* Vector # 651 */
(uint32_t) &dummy, /* Vector # 652 */
(uint32_t) &dummy, /* Vector # 653 */
(uint32_t) &dummy, /* Vector # 654 */
(uint32_t) &dummy, /* Vector # 655 RF0	FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 656 COF0	FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 657 CAF0	FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 658 RF1	FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 659 COF1	FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 660 CAF1	FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 661 RF2	FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 662 COF2	FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 663 CAF2	FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 664 RF3	FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 665 COF3	FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 666 CAF3	FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 667 FFLAG	FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 668 REF	FlexPWM_0 */
(uint32_t) &dummy, /* Vector # 669 */
(uint32_t) &dummy, /* Vector # 670 */
(uint32_t) &dummy, /* Vector # 671 */
(uint32_t) &dummy, /* Vector # 672 */
(uint32_t) &dummy, /* Vector # 673 */
(uint32_t) &dummy, /* Vector # 674 */
(uint32_t) &dummy, /* Vector # 675 */
(uint32_t) &dummy, /* Vector # 676 */
(uint32_t) &dummy, /* Vector # 677 */
(uint32_t) &dummy, /* Vector # 678 */
(uint32_t) &dummy, /* Vector # 679 */
(uint32_t) &dummy, /* Vector # 680 */
(uint32_t) &dummy, /* Vector # 681 */
(uint32_t) &dummy, /* Vector # 682 */
(uint32_t) &dummy, /* Vector # 683 */
(uint32_t) &dummy, /* Vector # 684 */
(uint32_t) &dummy, /* Vector # 685 */
(uint32_t) &dummy, /* Vector # 686 */
(uint32_t) &dummy, /* Vector # 687 */
(uint32_t) &dummy, /* Vector # 688 */
(uint32_t) &dummy, /* Vector # 689 */
(uint32_t) &dummy, /* Vector # 690 */
(uint32_t) &dummy, /* Vector # 691 */
(uint32_t) &dummy, /* Vector # 692 */
(uint32_t) &dummy, /* Vector # 693 */
(uint32_t) &dummy, /* Vector # 694 */
(uint32_t) &dummy, /* Vector # 695 */
(uint32_t) &dummy, /* Vector # 696 */
(uint32_t) &dummy, /* Vector # 697 */
(uint32_t) &dummy, /* Vector # 698 */
(uint32_t) &dummy, /* Vector # 699 */
(uint32_t) &dummy, /* Vector # 700 MRS_I	CTU_0 */

(uint32_t) &dummy, /* Vector # 701 T0_I	CTU_0 */
(uint32_t) &dummy, /* Vector # 702 T1_I	CTU_0 */
(uint32_t) &dummy, /* Vector # 703 T2_I	CTU_0 */
(uint32_t) &dummy, /* Vector # 704 T3_I	CTU_0 */
(uint32_t) &dummy, /* Vector # 705 T4_I	CTU_0 */
(uint32_t) &dummy, /* Vector # 706 T5_I	CTU_0 */
(uint32_t) &dummy, /* Vector # 707 T6_I	CTU_0 */
(uint32_t) &dummy, /* Vector # 708 T7_I	CTU_0 */
(uint32_t) &dummy, /* Vector # 709 FIFO0_I	CTU_0 */
(uint32_t) &dummy, /* Vector # 710 FIFO1_I	CTU_0 */
(uint32_t) &dummy, /* Vector # 711 FIFO2_I	CTU_0 */
(uint32_t) &dummy, /* Vector # 712 FIFO3_I	CTU_0 */
(uint32_t) &dummy, /* Vector # 713 ADC_I	CTU_0 */
(uint32_t) &dummy, /* Vector # 714 ERR_I	CTU_0 */
(uint32_t) &dummy, /* Vector # 715 */
(uint32_t) &dummy, /* Vector # 716 */
(uint32_t) &dummy, /* Vector # 717 */
(uint32_t) &dummy, /* Vector # 718 */
(uint32_t) &dummy, /* Vector # 719 */
(uint32_t) &dummy, /* Vector # 720 */
(uint32_t) &dummy, /* Vector # 721 */
(uint32_t) &dummy, /* Vector # 722 */
(uint32_t) &dummy, /* Vector # 723 */
(uint32_t) &dummy, /* Vector # 724 */
(uint32_t) &dummy, /* Vector # 725 */
(uint32_t) &dummy, /* Vector # 726 */
(uint32_t) &dummy, /* Vector # 727 */
(uint32_t) &dummy, /* Vector # 728 */
(uint32_t) &dummy, /* Vector # 729 */
(uint32_t) &dummy, /* Vector # 730 */
(uint32_t) &dummy, /* Vector # 731 */
(uint32_t) &dummy, /* Vector # 732 */
(uint32_t) &dummy, /* Vector # 733 */
(uint32_t) &dummy, /* Vector # 734 IRQ0	SPT */
(uint32_t) &dummy, /* Vector # 735 IRQ1	SPT */
(uint32_t) &dummy, /* Vector # 736 ECS	SPT */
(uint32_t) &dummy, /* Vector # 737 DMA	SPT */
(uint32_t) &dummy, /* Vector # 738 combined IRQ	WGM (Waveform Generator Module) */
(uint32_t) &dummy, /* Vector # 739 combined IRQ	CTE (RADAR Cross Timing Engine) */
(uint32_t) &dummy, /* Vector # 740 */
(uint32_t) &dummy, /* Vector # 741 */
(uint32_t) &dummy, /* Vector # 742 */
(uint32_t) &dummy, /* Vector # 743 */
(uint32_t) &dummy, /* Vector # 744 */
(uint32_t) &dummy, /* Vector # 745 ADC value overload | overvolt	SDADC (RADAR Analog block) */
(uint32_t) &dummy, /* Vector # 746 Stable	XOSC (RADAR Analog block) */
(uint32_t) &dummy, /* Vector # 747 Lock	SDPLL (RADAR Analog block) */
(uint32_t) &dummy, /* Vector # 748 Loss of lock	SDPLL (RADAR Analog block) */
(uint32_t) &dummy, /* Vector # 749 Loss of reference clock	SDPLL (RADAR Analog block) */
(uint32_t) &dummy, /* Vector # 750 IRQ	CSE */
(uint32_t) &dummy, /* Vector # 751 DPHY_INT	MIPICSI2 */
(uint32_t) &dummy, /* Vector # 752 ERR_INT	MIPICSI2 */
(uint32_t) &dummy, /* Vector # 753 VC_INT	MIPICSI2 */
(uint32_t) &dummy, /* Vector # 754 JTAGM_INT	JTAGM */

};


void dummy (void) {   /* Dummy ISR vector to trap undefined ISRs */
    while (1) {};  /* Wait forever or for watchdog timeout */
}

