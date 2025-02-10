#include "generatepdf.h"

#include <iostream>
#include <QImage>
#include <QIODevice>
#include <QBuffer>
#include <QDebug>

PDFGenerator::PDFGenerator(const char* font_path) {
    pdf = HPDF_New(error_handler, nullptr);
    if (!pdf) {
        std::cerr << "Failed to create PDF object" << std::endl;
        exit(1);
    }

    HPDF_UseUTFEncodings(pdf);
    HPDF_SetCurrentEncoder(pdf, "UTF-8");

    // 加载字体
    font_name = HPDF_LoadTTFontFromFile(pdf, font_path, HPDF_TRUE);
    font = HPDF_GetFont(pdf, font_name, "UTF-8");
    font_size = 12;
}

PDFGenerator::~PDFGenerator() {
    HPDF_Free(pdf);
}

void PDFGenerator::createPage() {
    page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    HPDF_Page_SetFontAndSize(page, font, font_size);
}

void PDFGenerator::drawText(float x, float y, const char* text) {
    float page_height = HPDF_Page_GetHeight(page);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, PDF_COORD_X(x), PDF_COORD_Y(y, page_height), text);
    HPDF_Page_EndText(page);
}

void PDFGenerator::drawTable(float x, float y, float width, float height, int rows, int cols) {
    float page_height = HPDF_Page_GetHeight(page);
    float cell_width = width / cols;
    float cell_height = height / rows;

    float start_x = PDF_COORD_X(x);
    float start_y = PDF_COORD_Y(y, page_height);

    // 绘制行
    for (int i = 0; i <= rows; ++i) {
        float current_y = start_y - i * cell_height;
        HPDF_Page_MoveTo(page, start_x, current_y);
        HPDF_Page_LineTo(page, start_x + width, current_y);
        HPDF_Page_Stroke(page);
    }

    // 绘制列
    for (int j = 0; j <= cols; ++j) {
        float current_x = start_x + j * cell_width;
        HPDF_Page_MoveTo(page, current_x, start_y);
        HPDF_Page_LineTo(page, current_x, start_y - height);
        HPDF_Page_Stroke(page);
    }
}

void PDFGenerator::saveToFile(const char* filename) {
    HPDF_SaveToFile(pdf, filename);
}

void PDFGenerator::drawCenteredTextInCell(float x, float y, float cell_width, float cell_height, const char *text) {
    float page_height = HPDF_Page_GetHeight(page);

    // 计算文本的宽度
    HPDF_REAL text_width = HPDF_Page_TextWidth(page, text);

    // 计算水平偏移量 (将文本居中)
    float offset_x = (cell_width - text_width) / 2;

    // 计算垂直偏移量 (将文本居中)
    float offset_y = (cell_height - font_size) / 2;  // 12 是字体大小

    // 使用计算出的偏移量来设置文本的位置
    float start_x = PDF_COORD_X(x) + offset_x;
    float start_y = PDF_COORD_Y(y, page_height) - offset_y;

    // 绘制文本
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, start_x, start_y, text);
    HPDF_Page_EndText(page);
}

void PDFGenerator::setFontSize(float size) {
    font_size = size;
    HPDF_Page_SetFontAndSize(page, font, font_size);  // 设置页面的字体大小
}

void PDFGenerator::addImageToPDF(const char* imagePath, float x, float y, float width, float height) {
    if (!pdf || !page) {
        std::cerr << "PDF page is not initialized!" << std::endl;
        return;
    }

    // 加载图片
    HPDF_Image image = HPDF_LoadJpegImageFromFile(pdf, imagePath);
    if (!image) {
        std::cerr << "Failed to load image from file: " << imagePath << std::endl;
        return;
    }

    // 使用左上角为 (0, 0) 的坐标系转换 y 坐标
    float convertedY = PDF_COORD_Y(y, HPDF_Page_GetHeight(page)) - height;

    // 绘制图像
    HPDF_Page_DrawImage(page, image, PDF_COORD_X(x), convertedY, width, height);
}

void PDFGenerator::drawIDCardNumber(const QString& idCard) {
    if (idCard.length() != 18) {
        std::cerr << "Invalid ID card number length. Expected 18 characters." << std::endl;
        return;
    }

    // 绘制每个数字到单独的格子中
    for (int i = 0; i < 18; ++i) {

        QString digit = idCard.mid(i, 1); // 取出每一位字符

        //        drawCenteredTextInCell(cellX, y, cellWidth, cellHeight, digit.toStdString().c_str());
        drawText(113 + i * 21.7,142, digit.toStdString().c_str());
    }
}

void PDFGenerator::drawRegisteredResidence(QString registeredResidence) {


    drawText(113 + 21.7,158, registeredResidence.toStdString().c_str());

}

void PDFGenerator::drawCurrentAddress(QString currentAddress) {

    drawText(113 + 21.7,174, currentAddress.toStdString().c_str());

}



void PDFGenerator::drawPersonalInformation(const QString name,const QString Alias,const QString Sex,const QString DOB)
{
    drawText(52, 125, name.toStdString().c_str());
    drawText(173, 125, Alias.toStdString().c_str());
    drawText(304, 125, Sex.toStdString().c_str());

    QStringList dobParts = DOB.split('-'); // Assuming format is always "YYYY-MM-DD"
    if (dobParts.size() == 3) {
        QString year = dobParts[0];
        QString month = dobParts[1];
        QString day = dobParts[2];

        // Draw year, month, and day at different positions
        drawText(425, 125, year.toStdString().c_str());
        drawText(490, 125, month.toStdString().c_str());
        drawText(533, 125, day.toStdString().c_str());
    } else {
        qDebug() << "Invalid DOB format: " << DOB;
    }
}

void PDFGenerator::drawPersonnelID(const QString PersonnelID) {
    if (PersonnelID.isEmpty()) {
        std::cerr << "Input text is empty. Nothing to draw." << std::endl;
        return;
    }

    // 遍历字符串的每个字符
    for (int i = 0; i < PersonnelID.length(); i++) {
        QString character = PersonnelID.mid(i, 1); // 获取当前字符

        drawText(34.6 + i * 8.3, 76.5, character.toStdString().c_str());
    }
}

void PDFGenerator::drawCardID(const QString CardID) {
    if (CardID.isEmpty()) {
        std::cerr << "Input text is empty. Nothing to draw." << std::endl;
        return;
    }

    // 遍历字符串的每个字符
    for (int i = 0; i < CardID.length(); i++) {
        QString character = CardID.mid(i, 1); // 获取当前字符

        drawText(440.6 + i * 6, 71, character.toStdString().c_str());
    }
}

void PDFGenerator::addImageFromBmpToPDF(const QString &bmpPath, float x, float y, float width, float height) {
    // 加载 BMP 图像
    QImage image(bmpPath);
    if (image.isNull()) {
        qWarning() << "Failed to load BMP image from:" << bmpPath;
        return;
    }

    // 转换为 JPG 数据并保存到内存
    QByteArray jpgData;
    QBuffer buffer(&jpgData);
    buffer.open(QIODevice::WriteOnly);
    if (!image.save(&buffer, "JPG")) {
        qWarning() << "Failed to convert BMP to JPG in memory.";
        return;
    }

    // 使用 HPDF_LoadJpegImageFromMem 加载 JPG 数据
    HPDF_Image pdfImage = HPDF_LoadJpegImageFromMem(pdf, reinterpret_cast<const HPDF_BYTE *>(jpgData.constData()), jpgData.size());
    if (!pdfImage) {
        qWarning() << "Failed to load JPG image from memory.";
        return;
    }

    // 添加图片到 PDF
    float pageHeight = HPDF_Page_GetHeight(page);
    HPDF_Page_DrawImage(page, pdfImage, PDF_COORD_X(x), PDF_COORD_Y(y + height, pageHeight), width, height);

    qDebug() << "BMP image added to PDF successfully from memory.";
}

void PDFGenerator::convertBmpToJpg(const QString &bmpPath, const QString &jpgPath) {
    // 加载 BMP 图像
    QImage image(bmpPath);
    if (image.isNull()) {
        qWarning() << "Failed to load BMP image from:" << bmpPath;
        return;
    }

    // 将图像保存为 JPG 格式
    if (!image.save(jpgPath, "JPG")) {
        qWarning() << "Failed to save JPG image to:" << jpgPath;
    } else {
        qDebug() << "BMP successfully converted to JPG:" << jpgPath;
    }
}

void PDFGenerator::error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
    std::cerr << "HPDF Error: " << error_no << ", Detail: " << detail_no << std::endl;
}
