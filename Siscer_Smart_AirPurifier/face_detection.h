#include "WiFiClient.h"
#include "driver/rtc_io.h"
#include "img_converters.h"
#include "fb_gfx.h"
#include "fd_forward.h"
#include "fr_forward.h"

WiFiClient client1;

mtmn_config_t mtmn_config = mtmn_init_config();

// Define color
#define COLOR_WHITE 0x00FFFFFF
#define COLOR_BLUE 0x00FF0000

unsigned long previousMillis = 0;
const long interval = 1000;

int KoorCX(int koor_x, int line_w) {
  Serial.println("KoorCX mid = " + String(koor_x + (line_w * 0.5) - 1));
  mid_x = koor_x + (line_w * 0.5) - 1;
  PenggerakL();
  return koor_x + (line_w * 0.5) - 1;
}

int KoorCY(int koor_y, int line_h) {
  Serial.println("KoorCY mid = " + String(koor_y + (line_h * 0.5) - 1) + "\n");
  return koor_y + (line_h * 0.5) - 1;
}

void draw_face_boxes(dl_matrix3du_t *image_matrix, box_array_t *boxes) {
  int x, y, w, h;
  uint32_t color = COLOR_WHITE, color1 = COLOR_BLUE;
  fb_data_t fb;
  fb.width = image_matrix->w;
  fb.height = image_matrix->h;
  fb.data = image_matrix->item;
  fb.bytes_per_pixel = 3;
  fb.format = FB_BGR888;

  for (int i = 0; i < boxes->len; i++) {
    x = (int)boxes->box[i].box_p[0];
    y = (int)boxes->box[i].box_p[1];
    w = (int)boxes->box[i].box_p[2] - x + 1;
    h = (int)boxes->box[i].box_p[3] - y + 1;

    fb_gfx_drawFastHLine(&fb, x, y, w, color);
    fb_gfx_drawFastHLine(&fb, x, y + h - 1, w, color);
    fb_gfx_drawFastVLine(&fb, x, y, h, color);
    fb_gfx_drawFastVLine(&fb, x + w - 1, y, h, color);

    int centerX = KoorCX(x, w);
    int centerY = KoorCY(y, h);
    int size = 10;

    for (int i = 0; i < size; i++) {
      fb_gfx_drawFastHLine(&fb, centerX, centerY + i, size, color1);
    }
  }
}

void TrackMuka() {
  while (!client1.connected()) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      Serial.println("No client connected");

      camera_fb_t *fb = esp_camera_fb_get();
      if (!fb) {
        break;
      }

      // Convert image to RGB format
      dl_matrix3du_t *image_matrix = dl_matrix3du_alloc(1, fb->width, fb->height, 3);
      if (!fmt2rgb888(fb->buf, fb->len, fb->format, image_matrix->item)) {
        Serial.println("fmt2rgb888 failed");
        dl_matrix3du_free(image_matrix);
        esp_camera_fb_return(fb);
        break;
      }

      // Detect faces
      box_array_t *boxes = face_detect(image_matrix, &mtmn_config);
      if (boxes) {
        draw_face_boxes(image_matrix, boxes);
        dl_lib_free(boxes->box);
        dl_lib_free(boxes);
      }

      // Convert the RGB image back to JPEG
      uint8_t *jpg_buf = NULL;
      size_t jpg_len = 0;
      bool jpeg_converted = fmt2jpg(image_matrix->item, image_matrix->w * image_matrix->h * 3, image_matrix->w, image_matrix->h, PIXFORMAT_RGB888, 90, &jpg_buf, &jpg_len);
      dl_matrix3du_free(image_matrix);
      if (!jpeg_converted) {
        esp_camera_fb_return(fb);
        break;
      }

      if (fb) {
        free(jpg_buf);
        esp_camera_fb_return(fb);
        break;
      }
    }
  }
}

void TrackMukaWeb() {
  while (client1.connected()) {
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
      client1.println("HTTP/1.1 500 Internal Server Error");
      client1.println("Content-Type: text/plain");
      client1.println("Connection: close");
      client1.println();
      break;
    }

    // Convert image to RGB format
    dl_matrix3du_t *image_matrix = dl_matrix3du_alloc(1, fb->width, fb->height, 3);
    if (!fmt2rgb888(fb->buf, fb->len, fb->format, image_matrix->item)) {
      Serial.println("fmt2rgb888 failed");
      dl_matrix3du_free(image_matrix);
      esp_camera_fb_return(fb);
      client1.println("HTTP/1.1 500 Internal Server Error");
      client1.println("Content-Type: text/plain");
      client1.println("Connection: close");
      client1.println();
      break;
    }

    // Detect faces
    box_array_t *boxes = face_detect(image_matrix, &mtmn_config);
    if (boxes) {
      draw_face_boxes(image_matrix, boxes);
      dl_lib_free(boxes->box);
      dl_lib_free(boxes);
    }

    // Convert the RGB image back to JPEG
    uint8_t *jpg_buf = NULL;
    size_t jpg_len = 0;
    bool jpeg_converted = fmt2jpg(image_matrix->item, image_matrix->w * image_matrix->h * 3, image_matrix->w, image_matrix->h, PIXFORMAT_RGB888, 90, &jpg_buf, &jpg_len);
    dl_matrix3du_free(image_matrix);
    if (!jpeg_converted) {
      Serial.println("JPEG compression failed");
      esp_camera_fb_return(fb);
      client1.println("HTTP/1.1 500 Internal Server Error");
      client1.println("Content-Type: text/plain");
      client1.println("Connection: close");
      client1.println();
      break;
    }

    if (fb) {
      client1.println("HTTP/1.1 200 OK");
      client1.println("Content-Type: image/jpeg");
      client1.println("Content-Length: " + String(jpg_len));
      client1.println();
      client1.write(jpg_buf, jpg_len);
      free(jpg_buf);
      esp_camera_fb_return(fb);
      break;
    }
  }
}