#include "../includes/Pcm.hpp"

Pcm::Pcm(std::string const &device, snd_pcm_stream_t stream)
{
	int rc;

	rc = snd_pcm_open(&_handle, device.c_str(), stream, 0);
	if (rc < 0)
	{
		std::cout << "Unable to open pcm device for capture: " << snd_strerror(rc) << std::endl;
		exit(EXIT_FAILURE);
	}

	rc = snd_pcm_set_params(_handle,
							PCM_FORMAT,
							PCM_ACCESS,
							PcmSetting::CHANNELS,
							PcmSetting::FRAME_RATE,
							SOFT_RESAMPLE,
							LATENCY);
	if (rc < 0)
	{
		std::cout << "Pcm hardware settings error\n"
				  << std::endl;
		exit(EXIT_FAILURE);
	}
}

Pcm::~Pcm()
{
	snd_pcm_close(_handle);
}