#if __has_include(<Arduino.h>)
#include <Arduino.h>
#include <Wire.h>
#else
#include <stdint.h>
#include <esp_idf_version.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
uint32_t millis() { return pdTICKS_TO_MS(xTaskGetTickCount()); }
void loop();
#endif
#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_ops.h>
#include <esp_lcd_panel_vendor.h>
#include <esp_lcd_panel_ili9342.h>
#include <esp_i2c.hpp>
#include <m5core2_power.hpp> // AXP192 power management (core2)
#include <uix.hpp> // user interface library
#include <gfx.hpp> // graphics library
//#define SYNNOVA_REGULAR_IMPLEMENTATION
//#include "assets/SYNNova_Regular.hpp"
//#define BUNGEE_REGULAR_IMPLEMENTATION
//#include "assets/Bungee_Regular.hpp"
//#define TELEGRAMA_IMPLEMENTATION
//#include "assets/telegrama.hpp"
#define OPENSANS_REGULAR_IMPLEMENTATION
#include "assets/OpenSans_Regular.hpp"
//#define VGA_8X8_IMPLEMENTATION
//#include "assets/vga_8x8.hpp"
//#define NOTOSANSBOLD15_IMPLEMENTATION
//#include "assets/NotoSansBold15.hpp"
#include "flex_font.hpp"

using namespace gfx; // graphics
using namespace uix; // user interface
#ifdef ARDUINO
using namespace arduino;
#else
using namespace esp_idf;
#endif

using power_t = m5core2_power;
// for AXP192 power management
static power_t power(esp_i2c<1,21,22>::instance);

using color_t = gfx::color<gfx::rgb_pixel<16>>; // native
using color32_t = gfx::color<gfx::rgba_pixel<32>>; // uix

// the screen template instantiation aliases
using screen_t = uix::screen<gfx::rgb_pixel<16>>;
using surface_t = screen_t::control_surface_type;


template<typename ControlSurfaceType>
class font_box : public uix::control<ControlSurfaceType> {
   public:
    using control_surface_type = ControlSurfaceType;
    using base_type = uix::control<control_surface_type>;
    using pixel_type = typename base_type::pixel_type;
    using palette_type = typename base_type::palette_type;
    using color_type = gfx::color<pixel_type>;
    using color32_type = gfx::color<gfx::rgba_pixel<32>>;
   private:
    struct draw_cb_state {
        control_surface_type* dst;
        srect16 clip;
    };
    font_draw_cache m_font_draw_cache;
    font_measure_cache m_font_measure_cache;
    //win_font m_font;
    tt_font m_font;
    //::vlw_font m_font;
    srect16 m_rect;
    constexpr static const char* text = "helly\tworld\nfoo bar! puke";
    static gfx_result draw_cb(spoint16 location,const const_bitmap<alpha_pixel<8>>& glyph, void* state) {
        draw_cb_state* st = (draw_cb_state*)state;
        control_surface_type& dst = *(control_surface_type*)st->dst;
        const srect16 r(location,(ssize16)glyph.dimensions());
        draw::rectangle(dst,r,color_t::blue);
        if(r.intersects(st->clip)) {
            return draw::icon(dst,location,glyph,rgb_pixel<16>(rand()%32,rand()%64,rand()%32));
        } else {
            return gfx_result::success;
        }
    }
   public:
    font_box(uix::invalidation_tracker &parent, const palette_type *palette = nullptr)
        : base_type(parent, palette),m_font_draw_cache(malloc,realloc,free),m_font_measure_cache(malloc,realloc,free),
        m_font(OpenSans_Regular_stream,30,font_size_units::px) 
        //m_font(SYNNova_Regular_stream,30,font_size_units::px) 
        //m_font(Bungee_Regular_stream,25,font_size_units::px) 
        //m_font(telegrama_stream,30,font_size_units::px) 
        //m_font(vga_8x8_stream)
        //m_font(NotoSansBold15_stream)
    {
        
    }
    
    font_box(font_box &&rhs) : m_font(rhs.m_font) {
        do_move_control(rhs);
    }
    
    font_box &operator=(font_box &&rhs) {
        m_font = rhs.m_font;
        do_move_control(rhs);
        return *this;
    }
    font_box(const font_box &rhs) : m_font(rhs.m_font) {
        do_copy_control(rhs);
    }
    font_box &operator=(const font_box &rhs) {
        m_font = rhs.m_font;
        do_copy_control(rhs);
        return *this;
    }
    virtual ~font_box() {
       
    }
    void dump_stats() {
        puts("draw cache:");
        printf("\titems: %d/%d\n",(int)m_font_draw_cache.entries(), (int)m_font_draw_cache.max_entries());
        printf("\tmemory: %d/%d\n",(int)m_font_draw_cache.memory_size(), (int)m_font_draw_cache.max_memory_size());
        puts("measure cache:");
        printf("\titems: %d/%d\n",(int)m_font_measure_cache.entries(), (int)m_font_measure_cache.max_entries());
        printf("\tmemory: %d/%d\n",(int)m_font_measure_cache.memory_size(), (int)m_font_measure_cache.max_memory_size());
    }
    virtual void on_before_render() override {
        static int draw_state = 0;
        if(draw_state==0) {
            m_font_draw_cache.initialize();
            m_font_measure_cache.initialize();
            //m_font_draw_cache.max_memory_size();
            m_font_draw_cache.max_entries(20);
            m_font_measure_cache.max_memory_size(512);

            gfx_result res = m_font.initialize();
            if(gfx_result::success!=res) {
                printf("init error: %d\n",(int)res);
            }
            size16 area;
            res = m_font.measure(this->dimensions().width,text,&area,4,gfx_encoding::utf8,&m_font_measure_cache);
            if(gfx_result::success!=res) {
                printf("measure error: %d\n",(int)res);
            }
            m_rect = ((srect16)area.bounds()).center(this->bounds());
            ++draw_state;
        }
    }
    virtual void on_paint(control_surface_type &destination, const gfx::srect16 &clip) override {
        if(clip.intersects(m_rect)) {
            draw::rectangle(destination,m_rect,color_t::red);
            draw_cb_state state;
            state.dst = &destination;
            state.clip = clip;
            gfx_result res = m_font.draw(m_rect,text,draw_cb,&state,4,gfx_encoding::utf8,&m_font_draw_cache,&m_font_measure_cache);
            if(gfx_result::success!=res) {
                //printf("draw error: %d\n",(int)res);
            }
        }
    }
};
using font_box_t = font_box<surface_t>;

constexpr const size_t panel_transfer_buffer_size = 320*60*2;
extern uint8_t* panel_transfer_buffer1;
extern uint8_t* panel_transfer_buffer2;

// handle to the display
static esp_lcd_panel_handle_t panel_handle;
// the transfer buffers
uint8_t* panel_transfer_buffer1 = nullptr;
uint8_t* panel_transfer_buffer2 = nullptr;
// the currently active screen
static screen_t* panel_active_screen = nullptr;


// tell UIX the DMA transfer is complete
static bool panel_flush_ready(esp_lcd_panel_io_handle_t panel_io, 
                                esp_lcd_panel_io_event_data_t* edata, 
                                void* user_ctx) {
    if(panel_active_screen!=nullptr) {
        panel_active_screen->flush_complete();
    }
    return true;
}
// tell the lcd panel api to transfer data via DMA
static void panel_on_flush(const rect16& bounds, const void* bmp, void* state) {
    int x1 = bounds.x1, y1 = bounds.y1, x2 = bounds.x2 + 1, y2 = bounds.y2 + 1;
    esp_lcd_panel_draw_bitmap(panel_handle, x1, y1, x2, y2, (void*)bmp);
}

void panel_set_active_screen(screen_t& new_screen) {
    if(panel_active_screen!=nullptr) {
        // wait until any DMA transfer is complete
        while(panel_active_screen->flushing()) {
            vTaskDelay(5);
        }
        panel_active_screen->on_flush_callback(nullptr);
    }
    panel_active_screen=&new_screen;
    new_screen.on_flush_callback(panel_on_flush);
    panel_active_screen->invalidate();
}
void panel_update() {
    if(panel_active_screen!=nullptr) {
        panel_active_screen->update();    
    }
}

// initialize the screen using the esp panel API
void panel_init() {
    panel_transfer_buffer1 = (uint8_t*)heap_caps_malloc(panel_transfer_buffer_size,MALLOC_CAP_DMA);
    panel_transfer_buffer2 = (uint8_t*)heap_caps_malloc(panel_transfer_buffer_size,MALLOC_CAP_DMA);
    if(panel_transfer_buffer1==nullptr||panel_transfer_buffer2==nullptr) {
        puts("Out of memory allocating transfer buffers");
        while(1) vTaskDelay(5);
    }
    spi_bus_config_t buscfg;
    memset(&buscfg, 0, sizeof(buscfg));
    buscfg.sclk_io_num = 18;
    buscfg.mosi_io_num = 23;
    buscfg.miso_io_num = -1;
    buscfg.quadwp_io_num = -1;
    buscfg.quadhd_io_num = -1;
    buscfg.max_transfer_sz = panel_transfer_buffer_size + 8;

    // Initialize the SPI bus on VSPI (SPI3)
    spi_bus_initialize(SPI3_HOST, &buscfg, SPI_DMA_CH_AUTO);

    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_spi_config_t io_config;
    memset(&io_config, 0, sizeof(io_config));
    io_config.dc_gpio_num = 15,
    io_config.cs_gpio_num = 5,
    io_config.pclk_hz = 40*1000*1000,
    io_config.lcd_cmd_bits = 8,
    io_config.lcd_param_bits = 8,
    io_config.spi_mode = 0,
    io_config.trans_queue_depth = 10,
    io_config.on_color_trans_done = panel_flush_ready;
    // Attach the LCD to the SPI bus
    esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI3_HOST, &io_config, &io_handle);

    panel_handle = NULL;
    esp_lcd_panel_dev_config_t panel_config;
    memset(&panel_config, 0, sizeof(panel_config));
    panel_config.reset_gpio_num = -1;
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
    panel_config.rgb_endian = LCD_RGB_ENDIAN_BGR;
#else
    panel_config.color_space = ESP_LCD_COLOR_SPACE_BGR;
#endif
    panel_config.bits_per_pixel = 16;

    // Initialize the LCD configuration
    esp_lcd_new_panel_ili9342(io_handle, &panel_config, &panel_handle);

    // Reset the display
    esp_lcd_panel_reset(panel_handle);

    // Initialize LCD panel
    esp_lcd_panel_init(panel_handle);
    // esp_lcd_panel_io_tx_param(io_handle, LCD_CMD_SLPOUT, NULL, 0);
    //  Swap x and y axis (Different LCD screens may need different options)
    esp_lcd_panel_swap_xy(panel_handle, false);
    esp_lcd_panel_set_gap(panel_handle, 0, 0);
    esp_lcd_panel_mirror(panel_handle, false, false);
    esp_lcd_panel_invert_color(panel_handle, true);
    // Turn on the screen
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
    esp_lcd_panel_disp_on_off(panel_handle, true);
#else
    esp_lcd_panel_disp_off(panel_handle, true);
#endif
}

// the screen/control definitions
screen_t main_screen;
font_box_t main_box(main_screen);


#ifdef ARDUINO
void setup() {
    Serial.begin(115200);
    Serial.printf("Arduino version: %d.%d.%d\n",ESP_ARDUINO_VERSION_MAJOR,ESP_ARDUINO_VERSION_MINOR,ESP_ARDUINO_VERSION_PATCH);
#else
static void loop_task(void* arg) {
    uint32_t time_ts = millis();
    while(1) {
        loop();
        if(millis()>time_ts+150) {
            time_ts = millis();
            vTaskDelay(1);
        }
    }
}
extern "C" void app_main() {
    printf("ESP-IDF version: %d.%d.%d\n",ESP_IDF_VERSION_MAJOR,ESP_IDF_VERSION_MINOR,ESP_IDF_VERSION_PATCH);
#endif
    power.initialize(); // do this first
    panel_init(); // do this next
    // init the screen and callbacks
    main_screen.dimensions({320,240});
    main_screen.buffer_size(panel_transfer_buffer_size);
    main_screen.buffer1(panel_transfer_buffer1);
    main_screen.buffer2(panel_transfer_buffer2);
    main_screen.background_color(color_t::black);
    main_box.bounds(main_screen.bounds());
    main_screen.register_control(main_box);
    panel_set_active_screen(main_screen);
#ifndef ARDUINO
    TaskHandle_t handle;
    xTaskCreatePinnedToCore(loop_task,"loop_task",4096,nullptr,24,&handle,xTaskGetAffinity(xTaskGetCurrentTaskHandle()));
#endif
}

void loop()
{
    static int frames = 0;
    static int time_ts = millis();
    static long long total_ms = 0;
    uint32_t start_ts = millis();
    main_box.invalidate();
    panel_update();
    uint32_t end_ts = millis();
    total_ms += (end_ts-start_ts);
    ++frames;
    if(millis()>=time_ts+1000) {
        if(frames==0) {
            //printf("<1 FPS, Total: %dms\n",(int)total_ms);
        } else {
            //printf("%d FPS, Avg: %dms\n",frames,(int)(total_ms/frames));
        }
        //main_box.dump_stats();
        frames = 0;
        total_ms = 0;
        time_ts = millis();
    }
}
