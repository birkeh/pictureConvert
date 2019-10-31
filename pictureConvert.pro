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
    INCLUDEPATH += C:\dev\3rdParty\exiv2\include C:\dev\3rdParty\libraw xmp
    LIBS += -LC:\dev\3rdParty\exiv2\lib -lexiv2.dll -LC:\dev\3rdParty\libraw\lib -lraw -lws2_32 -lz
    QMAKE_CXXFLAGS += -DWIN_ENV -D_MSC_VER=1601 -DBUILDING_XMPCOMMON_LIB -DBUILDING_XMPCOMMON_AS_STATIC=1 -DBUILDING_XMPCORE_LIB
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
    dng/dng_big_table.cpp \
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
    dng/dng_local_string.cpp \
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
    dng/dng_safe_arithmetic.cpp \
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
    cmainwindow.cpp \
    xmp/XMPCommon/source/IConfigurable.cpp \
    xmp/XMPCommon/source/IConfigurationManager.cpp \
    xmp/XMPCommon/source/IError.cpp \
    xmp/XMPCommon/source/IErrorNotifier.cpp \
    xmp/XMPCommon/source/IUTF8String.cpp \
    xmp/XMPCore/source/IArrayNode.cpp \
    xmp/XMPCore/source/IClientDOMParser.cpp \
    xmp/XMPCore/source/IClientDOMSerializer.cpp \
    xmp/XMPCore/source/ICompositeNode.cpp \
    xmp/XMPCore/source/ICoreConfigurationManager.cpp \
    xmp/XMPCore/source/ICoreObjectFactory.cpp \
    xmp/XMPCore/source/IDOMImplementationRegistry.cpp \
    xmp/XMPCore/source/IDOMParser.cpp \
    xmp/XMPCore/source/IDOMSerializer.cpp \
    xmp/XMPCore/source/IMetadata.cpp \
    xmp/XMPCore/source/INameSpacePrefixMap.cpp \
    xmp/XMPCore/source/INode.cpp \
    xmp/XMPCore/source/INodeIterator.cpp \
    xmp/XMPCore/source/IPath.cpp \
    xmp/XMPCore/source/IPathSegment.cpp \
    xmp/XMPCore/source/ISimpleNode.cpp \
    xmp/XMPCore/source/IStructureNode.cpp

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
    dng/dng_big_table.h \
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
    dng/dng_local_string.h \
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
    dng/dng_safe_arithmetic.h \
    dng/dng_sdk_limits.h \
    dng/dng_shared.h \
    dng/dng_simd_type.h \
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
    dng/dng_xy_coord.h \
    xmp/TXMPFiles.hpp \
    xmp/TXMPIterator.hpp \
    xmp/TXMPMeta.hpp \
    xmp/TXMPUtils.hpp \
    xmp/XMP.hpp \
    xmp/XMP.incl_cpp \
    xmp/XMPCommon/Interfaces/BaseInterfaces/IConfigurable.h \
    xmp/XMPCommon/Interfaces/BaseInterfaces/ISharedObject.h \
    xmp/XMPCommon/Interfaces/BaseInterfaces/IThreadSafe.h \
    xmp/XMPCommon/Interfaces/BaseInterfaces/IVersionable.h \
    xmp/XMPCommon/Interfaces/IConfigurationManager.h \
    xmp/XMPCommon/Interfaces/IError.h \
    xmp/XMPCommon/Interfaces/IErrorNotifier.h \
    xmp/XMPCommon/Interfaces/IMemoryAllocator.h \
    xmp/XMPCommon/Interfaces/IObjectFactory.h \
    xmp/XMPCommon/Interfaces/IUTF8String.h \
    xmp/XMPCommon/Utilities/TWrapperFunctions.h \
    xmp/XMPCommon/Utilities/TWrapperFunctions2.h \
    xmp/XMPCommon/XMPCommonDefines.h \
    xmp/XMPCommon/XMPCommonErrorCodes.h \
    xmp/XMPCommon/XMPCommonFwdDeclarations.h \
    xmp/XMPCommon/XMPCommonLatestInterfaceVersions.h \
    xmp/XMPCore/Interfaces/IArrayNode.h \
    xmp/XMPCore/Interfaces/IClientDOMParser.h \
    xmp/XMPCore/Interfaces/IClientDOMSerializer.h \
    xmp/XMPCore/Interfaces/ICompositeNode.h \
    xmp/XMPCore/Interfaces/ICoreConfigurationManager.h \
    xmp/XMPCore/Interfaces/ICoreObjectFactory.h \
    xmp/XMPCore/Interfaces/IDOMImplementationRegistry.h \
    xmp/XMPCore/Interfaces/IDOMParser.h \
    xmp/XMPCore/Interfaces/IDOMSerializer.h \
    xmp/XMPCore/Interfaces/IMetadata.h \
    xmp/XMPCore/Interfaces/INameSpacePrefixMap.h \
    xmp/XMPCore/Interfaces/INode.h \
    xmp/XMPCore/Interfaces/INodeIterator.h \
    xmp/XMPCore/Interfaces/IPath.h \
    xmp/XMPCore/Interfaces/IPathSegment.h \
    xmp/XMPCore/Interfaces/ISimpleNode.h \
    xmp/XMPCore/Interfaces/IStructureNode.h \
    xmp/XMPCore/XMPCoreDefines.h \
    xmp/XMPCore/XMPCoreErrorCodes.h \
    xmp/XMPCore/XMPCoreFwdDeclarations.h \
    xmp/XMPCore/XMPCoreLatestInterfaceVersions.h \
    xmp/XMP_Const.h \
    xmp/XMP_Environment.h \
    xmp/XMP_IO.hpp \
    xmp/XMP_Version.h \
    xmp/client-glue/TXMPFiles.incl_cpp \
    xmp/client-glue/TXMPIterator.incl_cpp \
    xmp/client-glue/TXMPMeta.incl_cpp \
    xmp/client-glue/TXMPUtils.incl_cpp \
    xmp/client-glue/WXMPFiles.hpp \
    xmp/client-glue/WXMPIterator.hpp \
    xmp/client-glue/WXMPMeta.hpp \
    xmp/client-glue/WXMPUtils.hpp \
    xmp/client-glue/WXMP_Common.hpp

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
