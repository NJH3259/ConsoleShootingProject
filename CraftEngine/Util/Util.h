#pragma once

#include <Engine/Engine.h>
#include <Math/Vector2.h>

#include <random>
#include <string>
#include <cassert>

using namespace Craft;
namespace Util
{
    // 랜덤 엔진 반환 함수.
    inline std::mt19937& GetRandomEngine()
    {
        // 프로그램 실행 중 1번만 생성되는 랜덤 엔진.
        static std::mt19937 engine;
        return engine;
    }

    // 랜덤 시드 설정 함수.
    inline void SetRandomSeed()
    {
        // 하드웨어 기반 난수 생성기(시드 값 제공).
        std::random_device randomDevice;

        // 랜덤 엔진에 종자값(시드) 설정.
        GetRandomEngine().seed(randomDevice());
    }

    // 정수 난수 함수.
    inline int RandomRange(int min, int max)
    {
        // min에서 max까지 균등하게 부동소수점 난수를 생성해주는 분포 정의.
        std::uniform_int_distribution<int> distribution(min, max);

        // 난수 반환.
        return distribution(GetRandomEngine());
    }

    // 부동 소수점 난수 함수.
    inline float RandomRange(float min, float max)
    {
        // min에서 max까지 균등하게 부동소수점 난수를 생성해주는 분포 정의.
        std::uniform_real_distribution<float> distribution(min, max);

        // 난수 반환.
        return distribution(GetRandomEngine());
    }

    inline int GetUIOffset() { return Engine::Get().GetUIOffset(); }

    inline Vector2 GetScreenSize() { return Vector2(Engine::Get().GetConsoleWidth(), Engine::Get().GetConsoleHeight()); }

    inline std::string LoadImageFromFile(const std::string& fileName, const std::string& fileFolder)
    {
        std::string filePath = fileFolder + fileName;

        FILE* file = nullptr;
        fopen_s(&file, filePath.c_str(), "rt");

        if (!file)
        {
            assert(false && "Can't read Enemy.txt file");
            return nullptr;
        }

        //파일 내용을 저장할 버퍼 확인 후 파일 길이 확인
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);

        //파일 제일 끝위치 구한 후 처음으로 이동
        rewind(file);

        //파일을 저장할 버퍼
        char* buffer = new char[fileSize] {};

        //파일 읽기
        size_t readSize = fread(buffer, sizeof(char), fileSize, file);

        assert(readSize > 0 && "No data in the file");

        std::string actorImage(buffer, readSize);

        delete[] buffer;
        buffer = nullptr;

        fclose(file);

        return actorImage;
    }
}