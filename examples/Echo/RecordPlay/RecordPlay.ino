/*Press button to record,released button to playback*/

#include <M5Atom.h>

#if defined __has_include
#if __has_include(<esp_idf_version.h>)
#include <esp_idf_version.h>
#endif
#endif

#ifdef ESP_IDF_VERSION
#if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0))
#define USE_NEW_I2S_API 1
#include <ESP_I2S.h>
#else
#define USE_NEW_I2S_API 0
#include <driver/i2s.h>
#endif
#else
#define USE_NEW_I2S_API 0
#include <driver/i2s.h>
#endif

#define CONFIG_I2S_BCK_PIN     19
#define CONFIG_I2S_LRCK_PIN    33
#define CONFIG_I2S_DATA_PIN    22
#define CONFIG_I2S_DATA_IN_PIN 23

#define SPEAKER_I2S_NUMBER I2S_NUM_0

#define MODE_MIC  0
#define MODE_SPK  1
#define DATA_SIZE 1024

static constexpr uint32_t kSampleRate  = 16000;
static constexpr size_t kRecordTimeout = 100;

uint8_t microphonedata0[1024 * 70];
size_t data_offset = 0;

#if USE_NEW_I2S_API
I2SClass I2S;

static bool ConfigureNewI2SMic() {
    I2S.setPinsPdmRx(CONFIG_I2S_LRCK_PIN, CONFIG_I2S_DATA_IN_PIN);
    if (!I2S.begin(I2S_MODE_PDM_RX, kSampleRate, I2S_DATA_BIT_WIDTH_16BIT,
                   I2S_SLOT_MODE_MONO)) {
        return false;
    }

    i2s_pdm_rx_slot_config_t slot_cfg = I2S_PDM_RX_SLOT_DEFAULT_CONFIG(
        I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO);
    slot_cfg.slot_mask = I2S_PDM_SLOT_RIGHT;

    i2s_chan_handle_t rx_chan = I2S.rxChan();
    if (rx_chan == nullptr) {
        return false;
    }
    if (i2s_channel_disable(rx_chan) != ESP_OK) {
        return false;
    }
    if (i2s_channel_reconfig_pdm_rx_slot(rx_chan, &slot_cfg) != ESP_OK) {
        return false;
    }
    if (i2s_channel_enable(rx_chan) != ESP_OK) {
        return false;
    }
    return true;
}
#endif

bool InitI2SSpeakerOrMic(int mode) {
#if USE_NEW_I2S_API
    I2S.end();
    I2S.setTimeout(kRecordTimeout);

    if (mode == MODE_MIC) {
        return ConfigureNewI2SMic();
    }

    I2S.setPins(CONFIG_I2S_BCK_PIN, CONFIG_I2S_LRCK_PIN, CONFIG_I2S_DATA_PIN,
                -1, -1);
    return I2S.begin(I2S_MODE_STD, kSampleRate, I2S_DATA_BIT_WIDTH_16BIT,
                     I2S_SLOT_MODE_MONO, I2S_STD_SLOT_RIGHT);
#else
    esp_err_t err = ESP_OK;

    i2s_driver_uninstall(SPEAKER_I2S_NUMBER);
    i2s_config_t i2s_config = {
        .mode            = (i2s_mode_t)(I2S_MODE_MASTER),
        .sample_rate     = kSampleRate,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format  = I2S_CHANNEL_FMT_ALL_RIGHT,
#if ESP_IDF_VERSION > ESP_IDF_VERSION_VAL(4, 1, 0)
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
#else
        .communication_format = I2S_COMM_FORMAT_I2S,
#endif
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count    = 6,
        .dma_buf_len      = 60,
    };
    if (mode == MODE_MIC) {
        i2s_config.mode =
            (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM);
    } else {
        i2s_config.mode     = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
        i2s_config.use_apll = false;
        i2s_config.tx_desc_auto_clear = true;
    }

    err += i2s_driver_install(SPEAKER_I2S_NUMBER, &i2s_config, 0, NULL);
    i2s_pin_config_t tx_pin_config;

#if (ESP_IDF_VERSION > ESP_IDF_VERSION_VAL(4, 3, 0))
    tx_pin_config.mck_io_num = I2S_PIN_NO_CHANGE;
#endif
    tx_pin_config.bck_io_num   = CONFIG_I2S_BCK_PIN;
    tx_pin_config.ws_io_num    = CONFIG_I2S_LRCK_PIN;
    tx_pin_config.data_out_num = CONFIG_I2S_DATA_PIN;
    tx_pin_config.data_in_num  = CONFIG_I2S_DATA_IN_PIN;

    err += i2s_set_pin(SPEAKER_I2S_NUMBER, &tx_pin_config);
    err += i2s_set_clk(SPEAKER_I2S_NUMBER, kSampleRate,
                       I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
    return (err == ESP_OK);
#endif
}

size_t ReadMicData(uint8_t *buffer, size_t size) {
#if USE_NEW_I2S_API
    return I2S.readBytes((char *)buffer, size);
#else
    size_t bytes_read = 0;
    i2s_read(SPEAKER_I2S_NUMBER, (char *)buffer, size, &bytes_read,
             (kRecordTimeout / portTICK_RATE_MS));
    return bytes_read;
#endif
}

size_t WriteSpeakerData(const uint8_t *buffer, size_t size) {
#if USE_NEW_I2S_API
    return I2S.write(buffer, size);
#else
    size_t bytes_written = 0;
    i2s_write(SPEAKER_I2S_NUMBER, buffer, size, &bytes_written, portMAX_DELAY);
    return bytes_written;
#endif
}

void setup() {
    M5.begin(true, false, true);
    M5.dis.drawpix(0, CRGB(128, 128, 0));
    delay(2000);
}

void loop() {
    if (M5.Btn.isPressed()) {
        data_offset = 0;
        InitI2SSpeakerOrMic(MODE_MIC);
        M5.dis.drawpix(0, CRGB(128, 128, 0));

        while (1) {
            const size_t bytes_to_read =
                min<size_t>(DATA_SIZE, sizeof(microphonedata0) - data_offset);
            const size_t bytes_read =
                ReadMicData(microphonedata0 + data_offset, bytes_to_read);
            data_offset += bytes_read;
            M5.update();
            if (bytes_read == 0 || M5.Btn.isReleased() ||
                data_offset >= sizeof(microphonedata0))
                break;
        }

        InitI2SSpeakerOrMic(MODE_SPK);
        WriteSpeakerData(microphonedata0, data_offset);
    }
    M5.update();
}
