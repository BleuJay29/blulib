namespace Blu {
    class SoundImpl {
    public:
        ma_engine engine;
        ma_sound sound;
        float originalSampleRate;

        SoundImpl() : originalSampleRate(44100.0f){
            ma_engine_init(nullptr, &engine);
        }

        ~SoundImpl() {
            ma_sound_uninit(&sound);
            ma_engine_uninit(&engine);
        }

        bool load(const char* filename) {
            if (ma_sound_init_from_file(&engine, filename, 0, nullptr, nullptr, &sound) != MA_SUCCESS) {
                return false;
            }
           
            originalSampleRate = ma_engine_get_sample_rate(&engine); 
            return true;
        }

        void play() {
            ma_sound_start(&sound);
        }

        void stop() {
            ma_sound_stop(&sound);
        }

        void setPitch(float pitch) {
            ma_sound_set_pitch(&sound, pitch);
        }

        void setHertz(float hertz) {
            float pitch = hertz / originalSampleRate;
            ma_sound_set_pitch(&sound, pitch);
        }
    };



    Sound::Sound() : pImpl(new SoundImpl()) {}

    Sound::~Sound() {
        delete pImpl;
    }

    bool Sound::load(const char* filename) {
        return pImpl->load(filename);
    }

    void Sound::play() {
        pImpl->play();
    }

    void Sound::stop() {
        pImpl->stop();
    }

    void Sound::setPitch(float pitch) {
        pImpl->setPitch(pitch);
    }

    void Sound::setHertz(float hertz) {
        pImpl->setHertz(hertz);
    }

}