/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 *
 * @Hardwares: M5Atom Voice
 *
 */
#include <HTTPClient.h>
#include <WiFi.h>

#ifdef ESP_IDF_VERSION
#if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0))
#define USE_NEW_I2S_API 1
#include <ESP_I2S.h>
I2SClass I2S;
#else
#define USE_NEW_I2S_API 0
#include <driver/i2s.h>
#endif
#else
#define USE_NEW_I2S_API 0
#include <driver/i2s.h>
#endif

#include "BaiduRest.h"
#include "M5Atom.h"

const char *WifiSSID = "wifi_ssid";
const char *WifiPWD  = "wifi_password";

#define CONFIG_I2S_BCK_PIN     19
#define CONFIG_I2S_LRCK_PIN    33
#define CONFIG_I2S_DATA_PIN    22
#define CONFIG_I2S_DATA_IN_PIN 23

#define SPEAK_I2S_NUMBER I2S_NUM_0

#define MODE_MIC 0
#define MODE_SPK 1

static constexpr uint32_t kSampleRate  = 16000;
static constexpr size_t kRecordTimeout = 100;

bool InitI2SSpeakOrMic(int mode);
size_t ReadMicData(uint8_t *buffer, size_t size);

BaiduRest rest;
static uint8_t microphonedata0[1024 * 70];
int16_t *buffptr;
uint32_t data_offset = 0;

void setup() {
    M5.begin(true, false, true);
    M5.dis.clear();

    Serial.println("Init Spaker");
    InitI2SSpeakOrMic(MODE_SPK);
    delay(100);

    Serial.println("Connecting Wifi");
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    WiFi.begin(WifiSSID, WifiPWD);

    M5.dis.drawpix(0, CRGB(0, 128, 0));

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print('.');
    }

    M5.dis.drawpix(0, CRGB(128, 0, 0));

    Serial.println("Connected.");

    rest.settoken("94b97e8bc3f8a246d454d4fdda11b74c");
}

#define DATA_SIZE 1024

String SpakeStr;
bool Spakeflag = false;

void loop() {
    if (M5.Btn.isPressed()) {
        data_offset = 0;
        Spakeflag   = false;
        InitI2SSpeakOrMic(MODE_MIC);
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
            // delay(60);
        }
        Serial.println("end");

        if (rest.Pcm2String(microphonedata0, data_offset, DEV_PID_MANDARIN,
                            &SpakeStr) != -1) {
            Serial.println(SpakeStr);
            Spakeflag = true;
            M5.dis.drawpix(0, CRGB(128, 0, 128));
        } else {
            M5.dis.drawpix(0, CRGB(0, 128, 0));
        }
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Wifi reconnect");
        WiFi.reconnect();
        while (WiFi.status() != WL_CONNECTED) {
            delay(100);
        }
    }
    M5.update();
    delay(100);
}

bool InitI2SSpeakOrMic(int mode) {
#if USE_NEW_I2S_API
    I2S.end();
    I2S.setTimeout(kRecordTimeout);

    if (mode == MODE_MIC) {
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

    I2S.setPins(CONFIG_I2S_BCK_PIN, CONFIG_I2S_LRCK_PIN, CONFIG_I2S_DATA_PIN,
                -1, -1);
    return I2S.begin(I2S_MODE_STD, kSampleRate, I2S_DATA_BIT_WIDTH_16BIT,
                     I2S_SLOT_MODE_MONO, I2S_STD_SLOT_RIGHT);
#else
    esp_err_t err = ESP_OK;

    i2s_driver_uninstall(SPEAK_I2S_NUMBER);
    i2s_config_t i2s_config = {
        .mode        = (i2s_mode_t)(I2S_MODE_MASTER),
        .sample_rate = kSampleRate,
        .bits_per_sample =
            I2S_BITS_PER_SAMPLE_16BIT,  // is fixed at 12bit, stereo, MSB
        .channel_format = I2S_CHANNEL_FMT_ALL_RIGHT,
#if ESP_IDF_VERSION > ESP_IDF_VERSION_VAL(4, 1, 0)
        .communication_format =
            I2S_COMM_FORMAT_STAND_I2S,  // Set the format of the communication.
#else  // 设置通讯格式
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

    Serial.println("Init i2s_driver_install");

    err += i2s_driver_install(SPEAK_I2S_NUMBER, &i2s_config, 0, NULL);
    i2s_pin_config_t tx_pin_config;

#if (ESP_IDF_VERSION > ESP_IDF_VERSION_VAL(4, 3, 0))
    tx_pin_config.mck_io_num = I2S_PIN_NO_CHANGE;
#endif
    tx_pin_config.bck_io_num   = CONFIG_I2S_BCK_PIN;
    tx_pin_config.ws_io_num    = CONFIG_I2S_LRCK_PIN;
    tx_pin_config.data_out_num = CONFIG_I2S_DATA_PIN;
    tx_pin_config.data_in_num  = CONFIG_I2S_DATA_IN_PIN;

    Serial.println("Init i2s_set_pin");
    err += i2s_set_pin(SPEAK_I2S_NUMBER, &tx_pin_config);
    Serial.println("Init i2s_set_clk");
    err += i2s_set_clk(SPEAK_I2S_NUMBER, kSampleRate, I2S_BITS_PER_SAMPLE_16BIT,
                       I2S_CHANNEL_MONO);

    return (err == ESP_OK);
#endif
}

size_t ReadMicData(uint8_t *buffer, size_t size) {
#if USE_NEW_I2S_API
    return I2S.readBytes((char *)buffer, size);
#else
    size_t bytes_read = 0;
    i2s_read(SPEAK_I2S_NUMBER, (char *)buffer, size, &bytes_read,
             (kRecordTimeout / portTICK_RATE_MS));
    return bytes_read;
#endif
}
