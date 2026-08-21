// #include "assetsimage.h"

// #include <misc/types/assets.h>

// #include <filesystem>

// namespace Qx
// {



// AssetsImage::AssetsImage(const std::string fileName):
//     AssetsFile{ fileName },
//     // m_displaySize{ 100, 100 },
//     m_mimeType{ MimeType::NONE }
// {
//     std::filesystem::path filePath(fileName);
//     std::string extension = filePath.extension().string();

//     extension = Qx::toLower( extension );

//     // std::transform(extension.begin(), extension.end(), extension.begin(),
//     //                [](unsigned char c){ return std::tolower(c); });
//     if( extension == ".svg" )
//         m_mimeType = MimeType::SVG;
//     else if( extension == ".png" )
//         m_mimeType = MimeType::PNG;
//     else
//         qx_assert( false, "Unsupported image file yet" );
// }



// std::string AssetsImage::mimeType() const
// {
//     switch ( m_mimeType ) {
//     case MimeType::SVG:
//         return "svg";
//     case MimeType::PNG:
//         return "png";
//     default:
//         qx_assert( false, "Unsupported image file, "
//                          "Make sure to update loaders "
//                          "in ThorVG::meson_options.txt.");
//         break;
//     }
//     return "";
// }



// // x_vector2 AssetsImage::displaySize() const
// // {
// //     return m_displaySize;
// // }

// // void AssetsImage::setDisplaySize(prv::x_px ww, prv::x_px hh)
// // {
// //     m_displaySize = { ww,hh };
// // }



// }
