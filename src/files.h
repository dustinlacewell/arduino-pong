#pragma once

#include <Adafruit_SPIFlash.h>
#include <SdFat.h>
#include <SPI.h>

class FileSystemManager
{
public:
    FileSystemManager() : flash(&flashTransport)
    {
        // Constructor
    }

    bool begin()
    {
        // Initialize flash library and check its chip ID.
        if (!flash.begin())
        {
            Serial.println(F("Error, failed to initialize flash chip!"));
            return false;
        } else {
            Serial.println(F("Flash chip ID: "));
            Serial.println(flash.getJEDECID(), HEX);
        }

        // First call begin to mount the filesystem.
        if (!fatfs.begin(&flash))
        {
            Serial.println(F("Error, failed to mount filesystem!"));
            return false;
        } else {
            Serial.println(F("Mounted filesystem!"));
        }

        return true;
    }

    void ls()
    {
        fatfs.ls();
    }

    bool writeFile(const String &path, const String &data)
    {
        File file = fatfs.open(path.c_str(), FILE_WRITE);
        if (!file)
        {
            return false;
        }

        size_t bytesWritten = file.print(data);
        file.close();
        return bytesWritten == data.length();
    }

    String readFile(const String &path)
    {
        File file = fatfs.open(path.c_str(), FILE_READ);
        if (!file)
        {
            return String();
        }

        String data;
        while (file.available())
        {
            data += (char)file.read();
        }

        file.close();
        return data;
    }

    bool writeBinaryFile(const String &path, const uint8_t *data, size_t length)
    {
        File file = fatfs.open(path.c_str(), FILE_WRITE | O_TRUNC | O_CREAT);

        if (!file)
            return false;

        file.seek(0);

        size_t bytesWritten = file.write(data, length);        

        file.flush();
        file.sync();
        file.close();

        bool success = bytesWritten == length;

        if (success)
            Serial.println("Wrote " + String(bytesWritten) + " bytes to " + path);
        else
            Serial.println("Failed to write " + String(length) + " bytes to " + path);

        return success;
    }

    // This method assumes the caller provides a buffer large enough for the file's contents
    bool readBinaryFile(const String &path, uint8_t *buffer, size_t length)
    {
        File file = fatfs.open(path.c_str(), FILE_READ);
        if (!file)
            return false;

        size_t bytesRead = file.read(buffer, length);
        file.close();

        bool success = bytesRead == length;

        if (success) {
            Serial.println("Read " + String(bytesRead) + " bytes from " + path);
        } else {
            Serial.println("Failed to read " + String(length) + " bytes from " + path);
        }

        return success;
    }

    bool exists(const String &path)
    {
        return fatfs.exists(path.c_str());
    }

    bool remove(const String &path)
    {
        return fatfs.remove(path.c_str());
    }

    bool mkdir(const String &path)
    {
        return fatfs.mkdir(path.c_str());
    }

    bool rmdir(const String &path)
    {
        return fatfs.rmdir(path.c_str());
    }

private:
    Adafruit_FlashTransport_QSPI flashTransport;
    Adafruit_SPIFlash flash;
    FatFileSystem fatfs;
};

FileSystemManager files = FileSystemManager();