#pragma once
#pragma pack (push, AE, 8)

enum class AE_SoundChannels : short {
	MONO   = 1,
	STEREO = 2
};

enum class AE_SoundFormat : short {
	UNSIGNED_PCM = 0,
	SIGNED_PCM   = 1,
	SIGNED_FLOAT = 2
};

enum class AE_SoundSampleSize : short {
	SSS_1 = 1,
	SSS_2 = 2,
	SSS_4 = 4
};

struct AE_SoundFormatInfo {
	double                rateF;         // 0
	AE_SoundChannels      num_channels;  // 8
	AE_SoundFormat        format;        // 10
	AE_SoundSampleSize    sample_size;   // 12
};  // 16bytes

struct AE_SoundWorld {
	AE_SoundFormatInfo    fi;           // 0
	int                   num_samples;  // 16
	void                  *dataP;       // 24
};  // 32bytes

#pragma pack (pop, AE)
