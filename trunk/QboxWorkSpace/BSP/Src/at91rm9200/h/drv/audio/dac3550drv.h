/* sb16drv.h - global comment */

/* Copyright 1984-2001 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,21sep01,dat  Fix ANSI violations for diab compiler
01b,03feb00,jk   updated to reflect new sb16drv.c code drop.
01a,14oct99,jk   extracted from file sb16drv.c.
*/

/*
DESCRIPTION

*/

#ifndef __INCdac3550drvh
#define __INCdac3550drvh

#include "iosLib.h"
#include "msgQLib.h"
#include "drv/audio/sound_ioctl.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define MCK	60000000
#define FILE_SAMPLING_FREQ	44100 

/* Constant declarations used by I2S mode*/
#define SLOT_BY_FRAME	2
#define BITS_BY_SLOT	16
/* IRQ level declaration */
#define IRQ_LEVEL_I2S	5	

/* SSC_TCMR  configuration for I2S setting*/
/* I2S_ASY_MASTER_TX_SETTING(BITS_BY_SLOT, SLOT_BY_FRAME);*/
#define I2S_ASY_MASTER_TX_SETTING(nb_bit_by_slot, nb_slot_by_frame)( + \
AT91C_SSC_CKS_DIV   + \
AT91C_SSC_CKO_CONTINOUS      + \
AT91C_SSC_START_FALL_RF + \
((1<<16) & AT91C_SSC_STTDLY) + \
((((nb_bit_by_slot*nb_slot_by_frame)/2)-1) <<24))

/* Configuration to set in the SSC_TFMR Transmit Frame Mode Register
 Parameters : nb_bit_by_slot : 8, 16 or 32 bits
 			 nb_slot_by_frame : number of channels */
#define I2S_ASY_TX_FRAME_SETTING(nb_bit_by_slot, nb_slot_by_frame)( +\
(nb_bit_by_slot-1)  +\
AT91C_SSC_MSBF   +\
(((nb_slot_by_frame-1)<<8) & AT91C_SSC_DATNB)  +\
(((nb_bit_by_slot-1)<<16) & AT91C_SSC_FSLEN) +\
AT91C_SSC_FSOS_NEGATIVE)
/* I/O ports */

#define SBP( codec, x ) ( (codec) -> port + s_b_SB_##x )
#define SBP1( port, x ) ( (port) + s_b_SB_##x )

#define s_b_SB_RESET		0x6
#define s_b_SB_READ		0xa
#define s_b_SB_WRITE		0xc
#define s_b_SB_COMMAND		0xc
#define s_b_SB_STATUS		0xc
#define s_b_SB_DATA_AVAIL	0xe
#define s_b_SB_DATA_AVAIL_16 	0xf
#define s_b_SB_MIXER_ADDR	0x4
#define s_b_SB_MIXER_DATA	0x5
#define s_b_SB_OPL3_LEFT	0x0
#define s_b_SB_OPL3_RIGHT	0x2
#define s_b_SB_OPL3_BOTH	0x8

/* dsp commands
 */
#define SB_DSP_SAMPLE_RATE	0x40
#define SB_DSP_SAMPLE_RATE_OUT	0x41
#define SB_DSP_SAMPLE_RATE_IN	0x42
#define SB_DSP_MONO_8BIT	0xa0
#define SB_DSP_MONO_16BIT	0xa4
#define SB_DSP_STEREO_8BIT	0xa8
#define SB_DSP_STEREO_16BIT	0xac
#define SB_DSP4_OUT16_AI	0xb6
#define SB_DSP4_IN16_AI		0xbe
#define SB_DSP4_OUT8_AI		0xc6
#define SB_DSP4_IN8_AI		0xce
#define SB_DSP_DMA8_OFF		0xd0
#define SB_DSP_SPEAKER_ON	0xd1
#define SB_DSP_SPEAKER_OFF	0xd3
#define SB_DSP_DMA8_ON		0xd4
#define SB_DSP_DMA16_OFF	0xd5
#define SB_DSP_DMA16_ON		0xd6
#define SB_DSP_DMA16_EXIT       0xd9
#define SB_DSP_DMA8_EXIT        0xda
#define SB_DSP_GET_VERSION	0xe1

/* dsp input/output formats
 */
#define SB_DSP4_MODE_UNS_MONO		0x00
#define SB_DSP4_MODE_SIGN_MONO		0x10
#define SB_DSP4_MODE_UNS_STEREO		0x20
#define SB_DSP4_MODE_SIGN_STEREO	0x30

/* OPL3 commands
 */
#define TEST_REGISTER			0x01
#define TIMER_CONTROL_REGISTER		0x04	/* Left side */
#define CONNECTION_SELECT_REGISTER	0x04	/* Right side */
#define OPL3_MODE_REGISTER		0x05	/* Right side */
#define KEYON_BLOCK			0xb0	/* Left side ???*/
#define PERCUSSION_REGISTER		0xbd	/* Left side only */

#define TIMER1_REGISTER		0x02
#define TIMER2_REGISTER		0x03

/* TEST_REGISTER options
 */
#define ENABLE_WAVE_SELECT	0x20

/* TIMER_CONTROL_REGISTER options
 */
#define IRQ_RESET		0x80
#define TIMER1_MASK		0x40
#define TIMER2_MASK		0x20

/* OPL3_MODE_REGISTER options
 */
#define OPL3_ENABLE		0x01

/* Mixer commands
 */
#define SB_MIXER_MASTER_DEV	0x30
#define SB_MIXER_PCM_DEV	0x32
#define SB_MIXER_SYNTH_DEV	0x34
#define SB_MIXER_CD_DEV		0x36
#define SB_MIXER_LINE_DEV	0x38
#define SB_MIXER_MIC_DEV	0x3a
#define SB_MIXER_SPEAKER_DEV	0x3b
#define SB_MIXER_OUTPUT_SW	0x3c
#define SB_MIXER_IGAIN_DEV	0x3f
#define SB_MIXER_OGAIN_DEV	0x41
#define SB_MIXER_MIC_AGC	0x43
#define SB_MIXER_TREBLE_DEV	0x44
#define SB_MIXER_BASS_DEV	0x46
#define SB_MIXER_IRQ_NR		0x80
#define SB_MIXER_DMA_NR		0x81
#define SB_MIXER_IRQ_STAT	0x82
#define SB_MIXER_MPU_NR         0x84

#define RATE_MIN  4000
#define RATE_MAX 44100

#define MAX_DMA_MSGS 2
#define MAX_DMA_SIZE 32768

#define TASK_PRIORITY    0
#define TASK_OPTIONS     0
#define TASK_STACK_SIZE  2048

typedef struct
{
  char *name;
  int reg;
  int max_value;
  int shift;
  int unknownfield;
} MIXER_INFO;

#define	TWO_BUFF_EMPTY 0
#define	ONE_BUFF_READY 1
#define	TWO_BUFF_READY 2


typedef struct
{
  char *buffer;
  int length;
  int direction;
  int state;
} DMA_MSG;

typedef struct snd_fd_struct SND_FD;
typedef struct dsp_fd_struct DSP_FD;
typedef struct mixer_fd_struct MIXER_FD;

typedef struct
{
  DEV_HDR devHdr;

  unsigned long port;		/* base port of DSP chip */
  unsigned short mpu_port;	/* MPU port for SB DSP 4.0+ */
  unsigned short irq;		/* IRQ number of DSP chip */
  unsigned short dma8;		/* 8-bit DMA */
  unsigned short dma16;		/* 16-bit DMA */

  unsigned short version;	/* version of DSP chip */

  SEM_ID devSem;
  SEM_ID intSem;
  SEM_ID bufSem;
  MSG_Q_ID dmaQ;

  DSP_FD *pDsp;
/*  MIXER_FD *pMixer;*/

  int dmaIndex;

  int tid;
  int taskBusy;
  int dmaAuto;

} SND_DEV;

struct snd_fd_struct
{
  SND_DEV *pDev;

  FUNCPTR fdClose;
  FUNCPTR fdRead;
  FUNCPTR fdWrite;
  FUNCPTR fdIoctl;
};

struct dsp_fd_struct
{
  SND_FD dev;

  int dmaDirection;
  int dmaChannel;

  snd_info_t info;
};

struct mixer_fd_struct
{
  SND_FD dev;
};

typedef unsigned int UInt32; 
typedef unsigned short UInt16; 

typedef unsigned char Byte ;
typedef unsigned long u_long ;

typedef enum {
	Mono,					/* Monophonic sound (1 channel) */
	Stereo					/* Stereo sound (2 channels) */
} Chan;	
/*
 * These values represent values found in/or destined for a
 * WAV file.
 */
typedef struct {
	UInt32	SamplingRate;			/* Sampling rate in Hz */
	Chan	Channels;			/* Mono or Stereo */
	UInt32	Samples;			/* Sample count */	
	UInt16	DataBits;			/* Sample bit size (8/12/16) */
	UInt32	DataStart;			/* Offset to wav data */
	UInt32	DataBytes;			/* Data bytes in current chunk */
	char	bOvrSampling;			/* True if sampling_rate overrided */
	char	bOvrMode;			/* True if chan_mode overrided */
	char	bOvrBits;			/* True if data_bits is overrided */
} WAVINF;

/*
 * This structure manages an open WAV file.
 */
typedef struct {
	char	rw;				/* 'R' for read, 'W' for write */
	char	*Pathname;			/* Pathname of wav file */
	int	fd;				/* Open file descriptor or -1 */
	WAVINF	wavinfo;			/* WAV file hdr info */
        UInt32  num_samples;                    /* Total number of samples */
        UInt32  StartSample;                    /* First sample to play */
} WAVFILE;


/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

STATUS dac3550Drv (void);
DEV_HDR* dac3550DevCreate (char *devName, int port, int irq);
void  wavfile_free(WAVFILE *wfile);
WAVFILE * WavOpenForRead(const char *Pathname);
#else

STATUS dac3550Drv ();
DEV_HDR* dac3550DevCreate ();

void  wavfile_free();
WAVFILE * WavOpenForRead();
#endif  /* __STDC__ */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCsb16drvh */


