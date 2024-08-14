#include <flex_font.hpp>
#include <stdio.h>
using namespace gfx;
int font_draw_cache::hash_function(const int& key) {
    return key+5;
}
void font_draw_cache::expire_oldest(size_t new_data_size) {
    int min = m_min_accessed;
    while(m_cache.size() && (m_size+new_data_size)>m_max_size) {
        bool more_min = false;
        for(int i = 0;i<m_cache.size();++i) {
            map_t::value_type& v = *m_cache.at(i);
            if(v.value.accessed==min) {
                if(!more_min && (m_size+new_data_size)>m_max_size) {
                    m_size-=(v.value.dimensions.width*v.value.dimensions.height);
                    if(v.value.data!=nullptr) {
                        m_deallocator(v.value.data);
                    }
                    m_cache.remove(v.key);
                } else {
                    more_min = true;
                }
                break;
            } 
        }
        if(!more_min) {
            ++m_min_accessed;
        }
    }
    if(!m_cache.size()) {
        m_min_accessed=-1;
        m_max_accessed=-1;
    }
}
void font_draw_cache::reduce(size_t new_size) {
    int min = m_min_accessed;
    while(m_cache.size() && m_size>new_size) {
        bool more_min = false;
        for(int i = 0;i<m_cache.size();++i) {
            map_t::value_type& v = *m_cache.at(i);
            if(v.value.accessed==min) {
                if(!more_min && m_size>new_size) {
                    m_size-=(v.value.dimensions.width*v.value.dimensions.height);
                    if(v.value.data!=nullptr) {
                        m_deallocator(v.value.data);
                    }
                    m_cache.remove(v.key);
                } else {
                    more_min = true;
                }
                break;
            } 
        }
        if(!more_min) {
            ++m_min_accessed;
        }
    }
    if(!m_cache.size()) {
        m_min_accessed=-1;
        m_max_accessed=-1;
    }
}
font_draw_cache::font_draw_cache(void*(allocator)(size_t), void*(reallocator)(void*,size_t), void(deallocator)(void*)) : 
                                m_allocator(allocator),
                                m_reallocator(reallocator),
                                m_deallocator(deallocator),
                                m_initialized(false),
                                m_min_accessed(-1),
                                m_max_accessed(-1),
                                m_cache(hash_function,allocator,reallocator,deallocator),
                                m_size(0), 
                                m_max_size(0) {}
font_draw_cache::font_draw_cache(font_draw_cache&& rhs) : m_allocator(rhs.m_allocator),
                                m_reallocator(rhs.m_reallocator),
                                m_deallocator(rhs.m_deallocator),
                                m_initialized(rhs.m_initialized),
                                m_min_accessed(rhs.m_min_accessed),
                                m_max_accessed(rhs.m_max_accessed),
                                m_cache(rhs.m_cache),
                                m_size(rhs.m_size), 
                                m_max_size(rhs.m_max_size) {
}
font_draw_cache::~font_draw_cache() {
    deinitialize();
}
font_draw_cache& font_draw_cache::operator=(font_draw_cache&& rhs) {
    deinitialize();
    m_allocator=rhs.m_allocator;
    m_reallocator=rhs.m_reallocator;
    m_deallocator=rhs.m_deallocator;
    m_initialized=rhs.m_initialized;
    m_min_accessed=rhs.m_min_accessed;
    m_max_accessed=rhs.m_max_accessed;
    m_cache=helpers::gfx_move(rhs.m_cache);
    m_size=rhs.m_size;
    m_max_size=rhs.m_max_size;
    return *this;
}
size_t font_draw_cache::max_size() const {
    return m_max_size;
}
void font_draw_cache::max_size(size_t value) {
    if(value<1) {
        return;
    }
    if(m_size>value) {
        reduce(value);
    }
    m_max_size = value;
}
size_t font_draw_cache::size() const {
    return m_size;
}
gfx_result font_draw_cache::find(int codepoint, size16* out_dimensions,uint8_t** out_bitmap) const {
    const cache_entry_t* entry = m_cache.find(codepoint);
    if(entry==nullptr) {
        return gfx_result::canceled;
    }
    *out_bitmap=entry->data;
    *out_dimensions=entry->dimensions;
    return gfx_result::success;
}
void font_draw_cache::clear() {
    for(int i = 0;i<m_cache.size();++i) {
        uint8_t* p = m_cache.at(i)->value.data;
        if(p!=nullptr) {
            m_deallocator(p);
        }
    }
    m_cache.clear();
    m_min_accessed=-1;
    m_max_accessed=-1;
    m_size=0;
}
gfx::gfx_result font_draw_cache::initialize() {
    m_min_accessed=-1;
    m_max_accessed=-1;
    m_size=0;
    return gfx_result::success;
}
bool font_draw_cache::initialized() const {
    return m_initialized;
}
void font_draw_cache::deinitialize() {
    clear();
    m_initialized= false;
}
gfx_result font_draw_cache::add(int codepoint, size16 dimensions, const uint8_t* data) {
    size_t sz = dimensions.width*dimensions.height;
    if(sz==0) {
        return gfx_result::invalid_argument;
    }
    if(m_max_size==0) {
        return gfx_result::out_of_memory;
    }
    while(m_cache.size() && m_size+sz>m_max_size) {
        expire_oldest(sz);
    }
    if(m_size+sz>m_max_size) {
        return gfx_result::out_of_memory;
    }
    cache_entry_t entry;
    entry.data = (uint8_t*)m_allocator(sz);
    if(entry.data==nullptr) {
        return gfx_result::out_of_memory;
    }
    memcpy(entry.data,data,sz);
    entry.dimensions = dimensions;
    if(m_min_accessed==-1) {
        m_min_accessed = 0;
        m_max_accessed = 0;
    } else {
        ++m_max_accessed;
    }
    entry.accessed = m_max_accessed;
    if(!m_cache.insert({codepoint,entry})) {
        m_deallocator(entry.data);
        return gfx_result::out_of_memory;
    }
    return gfx_result::success;
}

int font_measure_cache::hash_function(const key_t& key) {
    int result = 0;
    const uint8_t* k = key.value;
    for(int i = 0;i<8;++i) {
        result|=~*(k++);
    }
    return result+5;
}
void font_measure_cache::make_key(int codepoint1, int codepoint2, key_t* key) {
    int32_t cp1 = codepoint1;
    int32_t cp2 = codepoint2;
    memcpy(key->value,&cp1,sizeof(int32_t));
    memcpy(key->value+sizeof(int32_t),&cp2,sizeof(int32_t));
}

void font_measure_cache::expire_oldest(size_t new_data_size) {
    int min = m_min_accessed;
    while(m_cache.size() && (m_size+new_data_size)>m_max_size) {
        bool more_min = false;
        for(int i = 0;i<m_cache.size();++i) {
            map_t::value_type& v = *m_cache.at(i);
            if(v.value.accessed==min) {
                if(!more_min && (m_size+new_data_size)>m_max_size) {
                    m_size-=sizeof(font_glyph_info);
                    m_cache.remove(v.key);
                } else {
                    more_min = true;
                }
                break;
            } 
        }
        if(!more_min) {
            ++m_min_accessed;
        }
    }
    if(!m_cache.size()) {
        m_min_accessed=-1;
        m_max_accessed=-1;
    }
}
void font_measure_cache::reduce(size_t new_size) {
    int min = m_min_accessed;
    while(m_cache.size() && m_size>new_size) {
        bool more_min = false;
        for(int i = 0;i<m_cache.size();++i) {
            map_t::value_type& v = *m_cache.at(i);
            if(v.value.accessed==min) {
                if(!more_min && m_size>new_size) {
                    m_size-=sizeof(font_glyph_info);
                    m_cache.remove(v.key);
                } else {
                    more_min = true;
                }
                break;
            } 
        }
        if(!more_min) {
            ++m_min_accessed;
        }
    }
    if(!m_cache.size()) {
        m_min_accessed=-1;
        m_max_accessed=-1;
    }
}
font_measure_cache::font_measure_cache(void*(allocator)(size_t), void*(reallocator)(void*,size_t), void(deallocator)(void*)) : 
                                m_allocator(allocator),
                                m_reallocator(reallocator),
                                m_deallocator(deallocator),
                                m_initialized(false),
                                m_min_accessed(-1),
                                m_max_accessed(-1),
                                m_cache(hash_function,allocator,reallocator,deallocator),
                                m_size(0), 
                                m_max_size(0) {}
font_measure_cache::font_measure_cache(font_measure_cache&& rhs) : m_allocator(rhs.m_allocator),
                                m_reallocator(rhs.m_reallocator),
                                m_deallocator(rhs.m_deallocator),
                                m_initialized(rhs.m_initialized),
                                m_min_accessed(rhs.m_min_accessed),
                                m_max_accessed(rhs.m_max_accessed),
                                m_cache(rhs.m_cache),
                                m_size(rhs.m_size), 
                                m_max_size(rhs.m_max_size) {
}
font_measure_cache::~font_measure_cache() {
    deinitialize();
}
font_measure_cache& font_measure_cache::operator=(font_measure_cache&& rhs) {
    deinitialize();
    m_allocator=rhs.m_allocator;
    m_reallocator=rhs.m_reallocator;
    m_deallocator=rhs.m_deallocator;
    m_initialized=rhs.m_initialized;
    m_min_accessed=rhs.m_min_accessed;
    m_max_accessed=rhs.m_max_accessed;
    m_cache=helpers::gfx_move(rhs.m_cache);
    m_size=rhs.m_size;
    m_max_size=rhs.m_max_size;
    return *this;
}
size_t font_measure_cache::max_size() const {
    return m_max_size;
}
void font_measure_cache::max_size(size_t value) {
    if(value<1) {
        return;
    }
    if(m_size>value) {
        reduce(value);
    }
    m_max_size = value;
}
size_t font_measure_cache::size() const {
    return m_size;
}
gfx_result font_measure_cache::find(int codepoint1, int codepoint2, font_glyph_info* out_glyph_info) const {
    key_t k;
    make_key(codepoint1,codepoint2,&k);
    const cache_entry_t* entry = m_cache.find(k);
    if(entry==nullptr) {
        return gfx_result::canceled;
    }
    *out_glyph_info = entry->data;
    return gfx_result::success;
}
void font_measure_cache::clear() {
    m_cache.clear();
    m_min_accessed=-1;
    m_max_accessed=-1;
    m_size=0;
}
gfx::gfx_result font_measure_cache::initialize() {
    m_min_accessed=-1;
    m_max_accessed=-1;
    m_size=0;
    return gfx_result::success;
}
bool font_measure_cache::initialized() const {
    return m_initialized;
}
void font_measure_cache::deinitialize() {
    clear();
    m_initialized= false;
}
gfx_result font_measure_cache::add(int codepoint1, int codepoint2, const font_glyph_info& glyph_info) {
    size_t sz = sizeof(font_glyph_info);
    if(m_max_size==0) {
        return gfx_result::out_of_memory;
    }
    while(m_cache.size() && m_size+sz>m_max_size) {
        expire_oldest(sz);
    }
    if(m_size+sz>m_max_size) {
        return gfx_result::out_of_memory;
    }
    cache_entry_t entry;
    entry.data = glyph_info;
    if(m_min_accessed==-1) {
        m_min_accessed = 0;
        m_max_accessed = 0;
    } else {
        ++m_max_accessed;
    }
    entry.accessed = m_max_accessed;
    key_t k;
    make_key(codepoint1,codepoint2,&k);
    if(!m_cache.insert({k,entry})) {
        return gfx_result::out_of_memory;
    }
    return gfx_result::success;
}
gfx_result font_base::measure(uint16_t max_width,const char* text, size16* out_area, uint16_t tab_width, gfx_encoding encoding, font_measure_cache* cache) const {
    if(text==nullptr || out_area==nullptr) {
        return gfx_result::invalid_argument;
    }
    if(cache!=nullptr&&cache->max_size()==0) {
        cache = nullptr;
    }
    const char* sz = text;
    size_t len = strlen(text);
    out_area->width = 0;
    out_area->height = 0;
    if(len==0) {
        return gfx_result::success;
    }
    uint16_t em_width = 0;
    uint16_t x_ext = 0, y_ext = 0;
    uint16_t x = 0,y=0;
    uint32_t cp=0, cp_next=0;
    size_t advlen = len;
    size_t advlen_next = 0;
    const uint16_t lineh = this->line_advance();
    gfx_result res = to_utf32(sz,&cp,&advlen,encoding);
    if(res!=gfx_result::success) {
        return res;
    }
    sz+=advlen;
    len-=advlen;
    if(*sz) {
        advlen_next = len;
        res = to_utf32(sz,&cp_next,&advlen_next,encoding);
        if(res!=gfx_result::success) {
            return res;
        }
        sz+=advlen_next;
        len-=advlen_next;
    }
    font_glyph_info em_gi;
    uint16_t xo, cw;
    bool cached;
    while(1) {
        font_glyph_info gi;
        switch(cp) {
            case '\t':
                if(em_width==0) {
                    cached = false;
                    if(cache!=nullptr) {
                        if(gfx_result::success==cache->find('M',0,&em_gi)) {
                            cached = true;
                        }
                    }
                    if(!cached) {
                        res=on_measure('M',0,&em_gi);
                        if(res!=gfx_result::success) {
                            return res;
                        }
                        if(cache!=nullptr) {
                            cache->add('M',0,em_gi);
                        }
                    }
                               
                    em_width=em_gi.advance_width;
                }
                cw = em_width*tab_width;
                x=((x/cw)+1)*cw;
                if(x>=max_width) {
                    x=0;
                    y+=lineh;
                }
                if(x>x_ext) {
                    x_ext = x;
                }
                break;
            case '\r':
                x=0;
                break;
            case '\n':
                y+=lineh;
                x=0;
                break;
            default:
                cached = false;
                if(cache!=nullptr) {
                    if(gfx_result::success==cache->find(cp,(int)(cp_next>=0x20)?cp_next:0,&gi)) {
                        cached = true;
                    }
                }
                if(!cached) {
                    res = this->on_measure((int)cp,(int)(cp_next>=0x20)?cp_next:0,&gi);
                    if(res!=gfx_result::success) {
                        return res;
                    }
                    if(cache!=nullptr) {
                        cache->add((int)cp,(int)cp_next,gi);
                    }
                }
                if(y+lineh>y_ext) {
                    y_ext = y+lineh;
                }
                xo=x+gi.dimensions.width+gi.offset.x;
                x+=gi.advance_width;
                if(xo>max_width) {
                    x=0;
                    xo = gi.dimensions.width+gi.offset.x;
                    y+=lineh;
                }
                if(xo>x_ext) {
                    x_ext = xo;
                }
                break;
        }
        cp = cp_next;
        if(!cp) {
            break;
        }
        // advance
        if(*sz) {
            advlen_next = len;
            res = to_utf32(sz,&cp_next,&advlen_next,encoding);
            if(res!=gfx_result::success) {
                return res;
            }
            sz+=advlen_next;
            len-=advlen_next;
        } else {
            cp_next = 0;
        }
    }
    out_area->width = x_ext;
    if(out_area->width>max_width) {
        out_area->width=max_width;
    }
    out_area->height = y_ext;
    return gfx_result::success;
}

gfx_result font_base::draw(const gfx::srect16& bounds, const char* text, font_draw_callback callback, void* callback_state, uint16_t tab_width, gfx::gfx_encoding encoding, font_draw_cache* draw_cache, font_measure_cache* measure_cache) const {
    using bmp_t = gfx::bitmap<alpha_pixel<8>>;
    if(text==nullptr || callback==nullptr) {
        return gfx_result::invalid_argument;
    }
    if(draw_cache!=nullptr&& draw_cache->max_size()==0) {
        // don't bother using it if it's disabled.
        draw_cache = nullptr;
    }
    if(measure_cache!=nullptr&& measure_cache->max_size()==0) {
        // don't bother using it if it's disabled.
        measure_cache = nullptr;
    }

    uint8_t* buffer = nullptr;
    size_t buffer_size = 0;
    const char* sz = text;
    size_t len = strlen(text);
    if(len==0) {
        return gfx_result::success;
    }
    uint16_t em_width = 0;
    uint16_t x_ext = 0, y_ext = 0;
    uint16_t x = 0,y=0;
    uint32_t cp=0, cp_next=0;
    size_t advlen = len;
    size_t advlen_next = 0;
    const uint16_t lineh = this->line_advance();
    //printf("line adv: %d\n",(int)lineh);
    gfx_result res = to_utf32(sz,&cp,&advlen,encoding);
    if(res!=gfx_result::success) {
        return res;
    }
    sz+=advlen;
    len-=advlen;
    if(*sz) {
        advlen_next = len;
        res = to_utf32(sz,&cp_next,&advlen_next,encoding);
        if(res!=gfx_result::success) {
            return res;
        }
        sz+=advlen_next;
        len-=advlen_next;
    }
    font_glyph_info em_gi;
    uint16_t xo, cw;
    bool cached;
    while(1) {
        font_glyph_info gi;
        switch(cp) {
            case '\t':
                if(em_width==0) {
                    cached = false;
                    if(measure_cache!=nullptr) {
                        if(gfx_result::success==measure_cache->find('M',0,&em_gi)) {
                            cached = true;
                        }
                    }
                    if(!cached) {
                        res=on_measure('M',0,&em_gi);
                        if(res!=gfx_result::success) {
                            if(buffer) {
                                free(buffer);
                            }
                            return res;
                        }
                        if(measure_cache!=nullptr) {
                            measure_cache->add('M',0,em_gi);
                        }
                    }
                    em_width = em_gi.advance_width;
                }
                
                cw = em_width*tab_width;
                x=((x/cw)+1)*cw;
                if(x>=bounds.width()) {
                    x=0;
                    y+=lineh;
                }
                if(x>x_ext) {
                    x_ext = x;
                }
                break;
            case '\r':
                x=0;
                break;
            case '\n':
                y+=lineh;
                x=0;
                break;
            default:
                cached = false;
                if(measure_cache!=nullptr) {
                    if(gfx_result::success==measure_cache->find(cp,(cp_next>=0x20)?cp_next:0,&gi)) {
                        cached = true;
                    }
                }
                if(!cached) {
                    res = this->on_measure((int)cp,(int)(cp_next>=0x20)?cp_next:0,&gi);
                    if(res!=gfx_result::success) {
                        if(buffer) {
                            free(buffer);
                        }
                        return res;
                    }
                    if(measure_cache!=nullptr) {
                        measure_cache->add(cp,(int)(cp_next>=0x20)?cp_next:0,gi);
                    }
                }
                gi.offset.y = y+lineh - gi.offset.y;
                
                if(cp>=0x20) { 
                    cached = false;
                    if(draw_cache!=nullptr) {
                        size16 d;
                        uint8_t* b;
                        if(gfx_result::success==draw_cache->find(cp,&d,&b)) {
                            bmp_t bmp(d,b);
                            spoint16 loc = spoint16(x,y).offset(bounds.point1()).offset(gi.offset);
                            callback(loc,bmp,callback_state);
                            cached = true;
                            //printf("cache hit for %c (%d)\n",(int)cp,(int)cp);
                        }
                    }
                    if(!cached) {
                        puts("cache miss");
                        // do draw
                        size_t bsize = bmp_t::sizeof_buffer(gi.dimensions);
                        if(buffer_size==0) {
                            buffer = (uint8_t*)malloc(bsize);
                            if(buffer==nullptr) {
                                return gfx_result::out_of_memory;
                            }
                            buffer_size = bsize;
                        } else {
                            if(buffer_size<bsize) {
                                buffer = (uint8_t*)realloc(buffer,bsize);
                                if(buffer==nullptr) {
                                    return gfx_result::out_of_memory;
                                }
                                buffer_size = bsize;
                            }
                        }
                        bmp_t bmp(gi.dimensions,buffer);
                        res = on_draw(bmp,cp,gi.glyph_index1);
                        if(res!=gfx_result::success) {
                            if(buffer) {
                                free(buffer);
                            }
                            return res;
                        }
                        if(draw_cache!=nullptr) {
                            draw_cache->add(cp,gi.dimensions,bmp.begin());
                            // don't care about errors here
                        }
                        spoint16 loc = spoint16(x,y).offset(bounds.point1()).offset(gi.offset);
                        //printf("loc: (%d,%d)\n",(int)loc.x,(int)loc.y);
                        callback(loc,bmp,callback_state);
                    }
                }
                if(y+lineh>y_ext) {
                    y_ext = y+lineh;
                }
                xo=x+gi.dimensions.width+gi.offset.x;
                x+=gi.advance_width;
                if(xo>bounds.width()) {
                    x=0;
                    xo = gi.dimensions.width+gi.offset.x;
                    y+=lineh;
                }
                if(xo>x_ext) {
                    x_ext = xo;
                }
                break;
        }
        cp = cp_next;
        if(!cp || y>bounds.y2) {
            break;
        }
        // advance
        if(*sz) {
            advlen_next = len;
            res = to_utf32(sz,&cp_next,&advlen_next,encoding);
            if(res!=gfx_result::success) {
                if(buffer) {
                    free(buffer);
                }
                return res;
            }
            sz+=advlen_next;
            len-=advlen_next;
        } else {
            cp_next = 0;
        }
    }
    if(buffer) {
        free(buffer);
    }
    return gfx_result::success;
}

