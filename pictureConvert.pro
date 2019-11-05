VERSION = 0.0.1.0
QMAKE_TARGET_COMPANY = WIN-DESIGN
QMAKE_TARGET_PRODUCT = pictureConvert
QMAKE_TARGET_DESCRIPTION = pictureConvert
QMAKE_TARGET_COPYRIGHT = (c) 2019 WIN-DESIGN

QT       += core gui sql multimedia concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

win32-msvc* {
    contains(QT_ARCH, i386) {
        message("msvc 32-bit")
    } else {
        message("msvc 64-bit")
    }
}

win32-g++ {
    message("mingw")
    INCLUDEPATH += C:\dev\3rdParty\exiv2\include C:\dev\3rdParty\libraw dng jpeg
    LIBS += -LC:\dev\3rdParty\exiv2\lib -lexiv2.dll -LC:\dev\3rdParty\libraw\lib -lraw -lws2_32 -lz
#    QMAKE_CXXFLAGS += -DWIN_ENV -D_MSC_VER=1601 -DBUILDING_XMPCOMMON_LIB -DBUILDING_XMPCOMMON_AS_STATIC=1 -DBUILDING_XMPCORE_LIB
}

unix {
    message("*nix")
    LIBS += -lraw -lexiv2
}

QMAKE_CXXFLAGS += -DLIBRAW_NODLL -DLIBRAW_NOTHREADS

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cdcp.cpp \
    cexif.cpp \
    cexportdialog.cpp \
    cimage.cpp \
    csplashscreen.cpp \
    ctreeview.cpp \
    dng/dng_1d_function.cpp \
    dng/dng_1d_table.cpp \
    dng/dng_abort_sniffer.cpp \
    dng/dng_area_task.cpp \
    dng/dng_bad_pixels.cpp \
    dng/dng_bottlenecks.cpp \
    dng/dng_camera_profile.cpp \
    dng/dng_color_space.cpp \
    dng/dng_color_spec.cpp \
    dng/dng_date_time.cpp \
    dng/dng_exceptions.cpp \
    dng/dng_exif.cpp \
    dng/dng_file_stream.cpp \
    dng/dng_filter_task.cpp \
    dng/dng_fingerprint.cpp \
    dng/dng_gain_map.cpp \
    dng/dng_globals.cpp \
    dng/dng_host.cpp \
    dng/dng_hue_sat_map.cpp \
    dng/dng_ifd.cpp \
    dng/dng_image.cpp \
    dng/dng_image_writer.cpp \
    dng/dng_info.cpp \
    dng/dng_iptc.cpp \
    dng/dng_jpeg_image.cpp \
    dng/dng_lens_correction.cpp \
    dng/dng_linearization_info.cpp \
    dng/dng_lossless_jpeg.cpp \
    dng/dng_matrix.cpp \
    dng/dng_memory.cpp \
    dng/dng_memory_stream.cpp \
    dng/dng_misc_opcodes.cpp \
    dng/dng_mosaic_info.cpp \
    dng/dng_mutex.cpp \
    dng/dng_negative.cpp \
    dng/dng_opcode_list.cpp \
    dng/dng_opcodes.cpp \
    dng/dng_orientation.cpp \
    dng/dng_parse_utils.cpp \
    dng/dng_pixel_buffer.cpp \
    dng/dng_point.cpp \
    dng/dng_preview.cpp \
    dng/dng_pthread.cpp \
    dng/dng_rational.cpp \
    dng/dng_read_image.cpp \
    dng/dng_rect.cpp \
    dng/dng_ref_counted_block.cpp \
    dng/dng_reference.cpp \
    dng/dng_render.cpp \
    dng/dng_resample.cpp \
    dng/dng_shared.cpp \
    dng/dng_simple_image.cpp \
    dng/dng_spline.cpp \
    dng/dng_stream.cpp \
    dng/dng_string.cpp \
    dng/dng_string_list.cpp \
    dng/dng_tag_types.cpp \
    dng/dng_temperature.cpp \
    dng/dng_tile_iterator.cpp \
    dng/dng_tone_curve.cpp \
    dng/dng_utils.cpp \
    dng/dng_validate.cpp \
    dng/dng_xmp.cpp \
    dng/dng_xmp_sdk.cpp \
    dng/dng_xy_coord.cpp \
    main.cpp \
    cmainwindow.cpp

HEADERS += \
    cdcp.h \
    cexif.h \
    cexportdialog.h \
    cimage.h \
    csplashscreen.h \
    cmainwindow.h \
    common.h \
    ctreeview.h \
    dng/RawEnvironment.h \
    dng/dng_1d_function.h \
    dng/dng_1d_table.h \
    dng/dng_abort_sniffer.h \
    dng/dng_area_task.h \
    dng/dng_assertions.h \
    dng/dng_auto_ptr.h \
    dng/dng_bad_pixels.h \
    dng/dng_bottlenecks.h \
    dng/dng_camera_profile.h \
    dng/dng_classes.h \
    dng/dng_color_space.h \
    dng/dng_color_spec.h \
    dng/dng_date_time.h \
    dng/dng_errors.h \
    dng/dng_exceptions.h \
    dng/dng_exif.h \
    dng/dng_fast_module.h \
    dng/dng_file_stream.h \
    dng/dng_filter_task.h \
    dng/dng_fingerprint.h \
    dng/dng_flags.h \
    dng/dng_gain_map.h \
    dng/dng_globals.h \
    dng/dng_host.h \
    dng/dng_hue_sat_map.h \
    dng/dng_ifd.h \
    dng/dng_image.h \
    dng/dng_image_writer.h \
    dng/dng_info.h \
    dng/dng_iptc.h \
    dng/dng_jpeg_image.h \
    dng/dng_lens_correction.h \
    dng/dng_linearization_info.h \
    dng/dng_lossless_jpeg.h \
    dng/dng_matrix.h \
    dng/dng_memory.h \
    dng/dng_memory_stream.h \
    dng/dng_misc_opcodes.h \
    dng/dng_mosaic_info.h \
    dng/dng_mutex.h \
    dng/dng_negative.h \
    dng/dng_opcode_list.h \
    dng/dng_opcodes.h \
    dng/dng_orientation.h \
    dng/dng_parse_utils.h \
    dng/dng_pixel_buffer.h \
    dng/dng_point.h \
    dng/dng_preview.h \
    dng/dng_pthread.h \
    dng/dng_rational.h \
    dng/dng_read_image.h \
    dng/dng_rect.h \
    dng/dng_ref_counted_block.h \
    dng/dng_reference.h \
    dng/dng_render.h \
    dng/dng_resample.h \
    dng/dng_sdk_limits.h \
    dng/dng_shared.h \
    dng/dng_simple_image.h \
    dng/dng_spline.h \
    dng/dng_stream.h \
    dng/dng_string.h \
    dng/dng_string_list.h \
    dng/dng_tag_codes.h \
    dng/dng_tag_types.h \
    dng/dng_tag_values.h \
    dng/dng_temperature.h \
    dng/dng_tile_iterator.h \
    dng/dng_tone_curve.h \
    dng/dng_types.h \
    dng/dng_uncopyable.h \
    dng/dng_utils.h \
    dng/dng_xmp.h \
    dng/dng_xmp_sdk.h \
    dng/dng_xy_coord.h

FORMS += \
    cexportdialog.ui \
    cmainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pictureconvert.qrc \
    qdarkstyle/style.qrc

DISTFILES += \
    README.md \
    LICENSE \
    jpeg/README \
    jpeg/aclocal.m4 \
    jpeg/ansi2knr.1 \
    jpeg/change.log \
    jpeg/cjpeg.1 \
    jpeg/coderules.txt \
    jpeg/config.guess \
    jpeg/config.sub \
    jpeg/configure \
    jpeg/configure.ac \
    jpeg/depcomp \
    jpeg/djpeg.1 \
    jpeg/filelist.txt \
    jpeg/install-sh \
    jpeg/install.txt \
    jpeg/jconfig.bcc \
    jpeg/jconfig.dj \
    jpeg/jconfig.mac \
    jpeg/jconfig.manx \
    jpeg/jconfig.mc6 \
    jpeg/jconfig.sas \
    jpeg/jconfig.st \
    jpeg/jconfig.txt \
    jpeg/jconfig.vms \
    jpeg/jconfig.wat \
    jpeg/jmemdosa.asm \
    jpeg/jpegtran.1 \
    jpeg/libjpeg.map \
    jpeg/libjpeg.txt \
    jpeg/ltmain.sh \
    jpeg/makcjpeg.st \
    jpeg/makdjpeg.st \
    jpeg/makeadsw.vc6 \
    jpeg/makeasln.v10 \
    jpeg/makecdep.vc6 \
    jpeg/makecdsp.vc6 \
    jpeg/makecfil.v10 \
    jpeg/makecmak.vc6 \
    jpeg/makecvcx.v10 \
    jpeg/makeddep.vc6 \
    jpeg/makeddsp.vc6 \
    jpeg/makedfil.v10 \
    jpeg/makedmak.vc6 \
    jpeg/makedvcx.v10 \
    jpeg/makejdep.vc6 \
    jpeg/makejdsp.vc6 \
    jpeg/makejdsw.vc6 \
    jpeg/makejfil.v10 \
    jpeg/makejmak.vc6 \
    jpeg/makejsln.v10 \
    jpeg/makejvcx.v10 \
    jpeg/makeproj.mac \
    jpeg/makerdep.vc6 \
    jpeg/makerdsp.vc6 \
    jpeg/makerfil.v10 \
    jpeg/makermak.vc6 \
    jpeg/makervcx.v10 \
    jpeg/maketdep.vc6 \
    jpeg/maketdsp.vc6 \
    jpeg/maketfil.v10 \
    jpeg/maketmak.vc6 \
    jpeg/maketvcx.v10 \
    jpeg/makewdep.vc6 \
    jpeg/makewdsp.vc6 \
    jpeg/makewfil.v10 \
    jpeg/makewmak.vc6 \
    jpeg/makewvcx.v10 \
    jpeg/makljpeg.st \
    jpeg/maktjpeg.st \
    jpeg/makvms.opt \
    jpeg/missing \
    jpeg/rdjpgcom.1 \
    jpeg/structure.txt \
    jpeg/testimg.bmp \
    jpeg/testimg.jpg \
    jpeg/testimg.ppm \
    jpeg/testimgp.jpg \
    jpeg/testorig.jpg \
    jpeg/testprog.jpg \
    jpeg/usage.txt \
    jpeg/wizard.txt \
    jpeg/wrjpgcom.1 \
    qdarkstyle/rc/branch_closed-on.png \
    qdarkstyle/rc/branch_closed.png \
    qdarkstyle/rc/branch_open-on.png \
    qdarkstyle/rc/branch_open.png \
    qdarkstyle/rc/checkbox_checked.png \
    qdarkstyle/rc/checkbox_checked_disabled.png \
    qdarkstyle/rc/checkbox_checked_focus.png \
    qdarkstyle/rc/checkbox_indeterminate.png \
    qdarkstyle/rc/checkbox_indeterminate_disabled.png \
    qdarkstyle/rc/checkbox_indeterminate_focus.png \
    qdarkstyle/rc/checkbox_unchecked.png \
    qdarkstyle/rc/checkbox_unchecked_disabled.png \
    qdarkstyle/rc/checkbox_unchecked_focus.png \
    qdarkstyle/rc/close-hover.png \
    qdarkstyle/rc/close-pressed.png \
    qdarkstyle/rc/close.png \
    qdarkstyle/rc/down_arrow.png \
    qdarkstyle/rc/down_arrow_disabled.png \
    qdarkstyle/rc/Hmovetoolbar.png \
    qdarkstyle/rc/Hsepartoolbar.png \
    qdarkstyle/rc/left_arrow.png \
    qdarkstyle/rc/left_arrow_disabled.png \
    qdarkstyle/rc/radio_checked.png \
    qdarkstyle/rc/radio_checked_disabled.png \
    qdarkstyle/rc/radio_checked_focus.png \
    qdarkstyle/rc/radio_unchecked.png \
    qdarkstyle/rc/radio_unchecked_disabled.png \
    qdarkstyle/rc/radio_unchecked_focus.png \
    qdarkstyle/rc/right_arrow.png \
    qdarkstyle/rc/right_arrow_disabled.png \
    qdarkstyle/rc/sizegrip.png \
    qdarkstyle/rc/stylesheet-branch-end.png \
    qdarkstyle/rc/stylesheet-branch-more.png \
    qdarkstyle/rc/stylesheet-vline.png \
    qdarkstyle/rc/transparent.png \
    qdarkstyle/rc/undock.png \
    qdarkstyle/rc/up_arrow.png \
    qdarkstyle/rc/up_arrow_disabled.png \
    qdarkstyle/rc/Vmovetoolbar.png \
    qdarkstyle/rc/Vsepartoolbar.png \
    qdarkstyle/style.qss
