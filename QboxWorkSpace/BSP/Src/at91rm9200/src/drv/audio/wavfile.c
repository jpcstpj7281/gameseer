#define WW_BADOUTPUTFILE	1
#define WW_BADWRITEHEADER	2

#define WR_BADALLOC		3
#define WR_BADSEEK		4
#define WR_BADRIFF		5
#define WR_BADWAVE		6
#define WR_BADFORMAT		7
#define WR_BADFORMATSIZE	8

#define WR_NOTPCMFORMAT		9
#define WR_NODATACHUNK		10
#define WR_BADFORMATDATA	11


#define		BUFFERSIZE   		1024
#define		PCM_WAVE_FORMAT   	1

#define		TRUE			1
#define		FALSE			0

typedef  struct
{	u_long     dwSize ;
	u_short    wFormatTag ;
	u_short    wChannels ;
	u_long     dwSamplesPerSec ;
	u_long     dwAvgBytesPerSec ;
	u_short    wBlockAlign ;
	u_short    wBitsPerSample ;
} WAVEFORMAT ;

typedef  struct
{	char    	RiffID [4] ;
	u_long    	RiffSize ;
	char    	WaveID [4] ;
	char    	FmtID  [4] ;
	u_long    	FmtSize ;
	u_short   	wFormatTag ;
	u_short   	nChannels ;
	u_long		nSamplesPerSec ;
	u_long		nAvgBytesPerSec ;
	u_short		nBlockAlign ;
	u_short		wBitsPerSample ;
	char		DataID [4] ;
	u_long		nDataBytes ;
} WAVE_HEADER ;

/*=================================================================================================*/

static char* findchunk  (char* pstart, char* fourcc, size_t n)
{	char	*pend ;
	int		k, test ;

	pend = pstart + n ;

	while (pstart < pend)
	{ 	if (*pstart == *fourcc)       /* found match for first char*/
		{	test = TRUE ;
			for (k = 1 ; fourcc [k] != 0 ; k++)
				test = (test ? ( pstart [k] == fourcc [k] ) : FALSE) ;
			if (test)
				return  pstart ;
			} ; /* if*/
		pstart ++ ;
		} ; /* while lpstart*/

	return  NULL ;
} ; /* findchuck*/

/*=================================================================================================*/


static  WAVE_HEADER  waveheader =
{	{ 'R', 'I', 'F', 'F' },
		0,
	{ 'W', 'A', 'V', 'E' },
	{ 'f', 'm', 't', ' ' },
		16,								/* FmtSize*/
		PCM_WAVE_FORMAT,						/* wFormatTag*/
		0,								/* nChannels*/
		0,
		0,
		0,
		0,
	{ 'd', 'a', 't', 'a' },
		0
} ; /* waveheader*/

static WAVFILE *
wavfile_alloc(const char *Pathname) {
	WAVFILE *wfile = (WAVFILE *) malloc(sizeof (WAVFILE));

	if ( wfile == NULL ) {
		return NULL;
	}

	memset(wfile,0,sizeof *wfile);
	
	if ( (wfile->Pathname = malloc(strlen(Pathname)+1)) == NULL ) {
		free(wfile);
		return NULL;
	}
	strcpy(wfile->Pathname,Pathname);
	wfile->fd = -1;				/* Initialize fd as not open */
	wfile->wavinfo.Channels = Mono;
	wfile->wavinfo.DataBits = 8;

	return wfile;
}
/*
 * Internal routine to release WAVFILE structure:
 * No errors reported.
 */
void
wavfile_free(WAVFILE *wfile) {
	if ( wfile->Pathname != NULL )
		free(wfile->Pathname);
	free(wfile);
}

int  WaveReadHeader  (int wavefile, int* channels, u_long* samplerate, int* samplebits, u_long* samples, u_long* datastart)
{	static  WAVEFORMAT  waveformat ;
	static	char   buffer [ BUFFERSIZE ] ;		/* Function is not reentrant.*/
	char*   ptr ;
	u_long  databytes ;



	if (lseek (wavefile, 0L, SEEK_SET)) {
		
		return  WR_BADSEEK ;
	}

	read (wavefile, buffer, BUFFERSIZE) ;

	if (findchunk (buffer, "RIFF", BUFFERSIZE) != buffer) {
		printErr("Bad format: Cannot find RIFF file marker");	/* wwg: Report error */
		return  WR_BADRIFF ;
	}

	if (! findchunk (buffer, "WAVE", BUFFERSIZE)) {
		printErr("Bad format: Cannot find WAVE file marker");	/* wwg: report error */
		return  WR_BADWAVE ;
	}

	ptr = findchunk (buffer, "fmt ", BUFFERSIZE) ;

	if (! ptr) {
		printErr("Bad format: Cannot find 'fmt' file marker");	/* wwg: report error */
		return  WR_BADFORMAT ;
	}

	ptr += 4 ;	/* Move past "fmt ".*/
	memcpy (&waveformat, ptr, sizeof (WAVEFORMAT)) ;

	if (waveformat.dwSize < (sizeof (WAVEFORMAT) - sizeof (u_long))) {
		printErr("Bad format: Bad fmt size");			/* wwg: report error */
		return  WR_BADFORMATSIZE ;
	}

	if (waveformat.wFormatTag != PCM_WAVE_FORMAT) {
		printErr("Only supports PCM wave format");			/* wwg: report error */
		return  WR_NOTPCMFORMAT ;
	}

	ptr = findchunk (buffer, "data", BUFFERSIZE) ;

	if (! ptr) {
		printErr("Bad format: unable to find 'data' file marker");	/* wwg: report error */
		return  WR_NODATACHUNK ;
	}

	ptr += 4 ;	/* Move past "data".*/
	memcpy (&databytes, ptr, sizeof (u_long)) ;

	/* Everything is now cool, so fill in output data.*/

	*channels   = waveformat.wChannels ;
	*samplerate = waveformat.dwSamplesPerSec ;
	*samplebits = waveformat.wBitsPerSample ;
	*samples    = databytes / waveformat.wBlockAlign ;
	
	*datastart  = ((u_long) (ptr + 4)) - ((u_long) (&(buffer[0]))) ;

	if (waveformat.dwSamplesPerSec != waveformat.dwAvgBytesPerSec / waveformat.wBlockAlign) {
		printErr("Bad file format");			/* wwg: report error */
		return  WR_BADFORMATDATA ;
	}

	if (waveformat.dwSamplesPerSec != waveformat.dwAvgBytesPerSec / waveformat.wChannels / ((waveformat.wBitsPerSample == 16) ? 2 : 1)) {
		printErr("Bad file format");			/* wwg: report error */
		return  WR_BADFORMATDATA ;
	}

  return  0 ;
} ; /* WaveReadHeader*/

WAVFILE *
WavOpenForRead(const char *Pathname) {
	WAVFILE *wfile = wavfile_alloc(Pathname);
	int e;					/* Saved errno value */
	UInt32 offset;				/* File offset */
	Byte ubuf[4];				/* 4 byte buffer */
	UInt32 dbytes;				/* Data byte count */
						/* wavfile.c values : */
	int channels;				/* Channels recorded in this wav file */
	u_long samplerate;			/* Sampling rate */
	int sample_bits;			/* data bit size (8/12/16) */
	u_long samples;				/* The number of samples in this file */
	u_long datastart;			/* The offset to the wav data */

	

	if ( wfile == NULL )
		return NULL;			/* Insufficient memory (class B msg) */

	/*
	 * Open the file for reading:
	 */
	if ( (wfile->fd = open(wfile->Pathname,O_RDONLY,0)) < 0 ) {
	
		goto errxit;
	}

	if ( lseek(wfile->fd,0L,SEEK_SET) != 0L ) {
		goto errxit;		/* Wav file must be seekable device */
	}

	if ( (e = WaveReadHeader(wfile->fd,&channels,&samplerate,&sample_bits,&samples,&datastart)) != 0 ) {
	
		goto errxit;
	}

	/*
	 * Copy WAV data over to WAVFILE struct:
	 */
	if ( channels == 2 )
		wfile->wavinfo.Channels = Stereo;
	else	wfile->wavinfo.Channels = Mono;

	wfile->wavinfo.SamplingRate = (UInt32) samplerate;
	wfile->wavinfo.Samples = (UInt32) samples;
	wfile->wavinfo.DataBits = (UInt16) sample_bits;
	wfile->wavinfo.DataStart = (UInt32) datastart;
        wfile->num_samples = wfile->wavinfo.Samples;
	wfile->rw = 'R';			/* Read mode */

	offset = wfile->wavinfo.DataStart - 4;

	/*
	 * Seek to byte count and read dbytes:
	 */
	if ( lseek(wfile->fd,offset,SEEK_SET) != offset ) {
	
		goto errxit;			/* Seek failure */
	}

	if ( read(wfile->fd,ubuf,4) != 4 ) {
	
		goto errxit;
	}

	/*
	 * Put little endian value into 32 bit value:
	 */
	dbytes = ubuf[3];
	dbytes = (dbytes << 8) | ubuf[2];
	dbytes = (dbytes << 8) | ubuf[1];
	dbytes = (dbytes << 8) | ubuf[0];

	wfile->wavinfo.DataBytes = dbytes;

	/*
	 * Open succeeded:
	 */
	return wfile;				/* Return open descriptor */

	/*
	 * Return error after failed open:
	 */
errxit:	e = errno;				/* Save errno */
	free(wfile->Pathname);			/* Dispose of copied pathname */
	free(wfile);				/* Dispose of WAVFILE struct */
	errno = e;				/* Restore error number */
	return NULL;				/* Return error indication */
}
