#ifndef PDFGENERATOR_H
#define PDFGENERATOR_H

#include <hpdf.h>
#include <QString>

#define PDF_COORD_X(x) (x)
#define PDF_COORD_Y(y, page_height) ((page_height) - (y))

class PDFGenerator {
public:
    PDFGenerator(const char* font_path);
    ~PDFGenerator(); // 析构函数声明

    void createPage();
    void drawText(float x, float y, const char* text);
    void drawTable(float x, float y, float width, float height, int rows, int cols);
    void saveToFile(const char* filename);
    void drawCenteredTextInCell(float x, float y, float cell_width, float cell_height, const char* text);
    void setFontSize(float size);

    void addImageToPDF(const char* imagePath, float x, float y, float width, float height);
    void drawIDCardNumber(const QString& idCard);
    void drawRegisteredResidence(QString registeredResidence);
    void drawCurrentAddress(QString currentAddress);
    void drawPersonalInformation(const QString name,const QString  Alias,const QString Sex,const  QString DOB);
    void drawPersonnelID(const QString PersonnelID);
    void drawCardID(const QString CardID);
    void addImageFromBmpToPDF(const QString &bmpPath, float x, float y, float width, float height);


    void convertBmpToJpg(const QString &bmpPath, const QString &jpgPath);




private:
    static void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data);

    HPDF_Doc pdf;
    HPDF_Page page;
    HPDF_Font font;
    const char* font_name;
    float font_size;
};

#endif // PDFGENERATOR_H
