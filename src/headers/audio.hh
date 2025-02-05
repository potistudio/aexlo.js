#pragma once
#pragma pack (push, AE, 8)
extern "C" {

enum class AE_SoundChannels : short {
	PF_Channels_MONO   = 1,
	PF_Channels_STEREO = 2
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
	double                rateF;
	AE_SoundChannels      num_channels;
	AE_SoundFormat        format;
	AE_SoundSampleSize    sample_size;
};

struct AE_SoundWorld {
	AE_SoundFormatInfo    fi;
	int                   num_samples;
	void                  *dataP;
};

}
#pragma pack (pop, AE)
