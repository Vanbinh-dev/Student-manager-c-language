#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

short isNumeric(char c);
short isAlpha(char c);
short isBlankOrEndl(char c);

short canBeFormatToInt(char* num);
short canBeFormatToDouble(char* num);

short isLegalContent(char *content);

#endif