/*
 * Splash Background renderer
 * Render all those things not supported as Image, with Splash
 *
 * Copyright (C) 2012,2013 Lu Wang <coolwanglu@gmail.com>
 */


#ifndef SPLASH_BACKGROUND_RENDERER_H__
#define SPLASH_BACKGROUND_RENDERER_H__

#include <string>

#include <splash/SplashBitmap.h>
#include <SplashOutputDev.h>

#include "pdf2htmlEX-config.h"

#include "Param.h"
#include "HTMLRenderer/HTMLRenderer.h"

namespace pdf2htmlEX {

// Based on BackgroundRenderer from poppler
class SplashBackgroundRenderer : public BackgroundRenderer, SplashOutputDev 
{
public:
  static const SplashColor white;
  //format: "png" or "jpg", or "" for a default format
  SplashBackgroundRenderer(const std::string & format, HTMLRenderer * html_renderer, const Param & param);

  void init(PDFDoc * doc) override;
  bool render_page(PDFDoc * doc, int pageno) override;
  void embed_image(int pageno) override;

  // Does this device use beginType3Char/endType3Char?  Otherwise,
  // text in Type 3 fonts will be drawn with drawChar/drawString.
  bool interpretType3Chars() override { return !param.process_type3; }

  void startPage(int pageNum, GfxState *state, XRef *xrefA) override;
  
  void drawChar(GfxState *state, double x, double y,
      double dx, double dy,
      double originX, double originY,
      CharCode code, int nBytes, const Unicode *u, int uLen) override;

  //for proof
  void beginTextObject(GfxState *state);
  void beginString(GfxState *state, const GooString * str);
  void endTextObject(GfxState *state);
  void updateRender(GfxState *state);

protected:
  HTMLRenderer * html_renderer;
  const Param & param;
  std::string format;
  int drawn_char_count;
};

} // namespace pdf2htmlEX

#endif // SPLASH_BACKGROUND_RENDERER_H__
