#include "sensor.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>     // array
#include <iostream>  // cout

#include "core_mocks.hpp"
#include "integers.hpp"

extern "C" {
FAKE_VOID_FUNC(SDL_SensorUpdate)
FAKE_VOID_FUNC(SDL_LockSensors)
FAKE_VOID_FUNC(SDL_UnlockSensors)
FAKE_VALUE_FUNC(int, SDL_NumSensors)
FAKE_VALUE_FUNC(int, SDL_SensorGetData, SDL_Sensor*, float*, int)

FAKE_VALUE_FUNC(SDL_SensorID, SDL_SensorGetInstanceID, SDL_Sensor*)
FAKE_VALUE_FUNC(SDL_SensorID, SDL_SensorGetDeviceInstanceID, int)

FAKE_VALUE_FUNC(SDL_SensorType, SDL_SensorGetType, SDL_Sensor*)
FAKE_VALUE_FUNC(SDL_SensorType, SDL_SensorGetDeviceType, int)

FAKE_VALUE_FUNC(int, SDL_SensorGetNonPortableType, SDL_Sensor*)
FAKE_VALUE_FUNC(int, SDL_SensorGetDeviceNonPortableType, int)

FAKE_VALUE_FUNC(const char*, SDL_SensorGetName, SDL_Sensor*)
FAKE_VALUE_FUNC(const char*, SDL_SensorGetDeviceName, int)
}

class SensorTest : public testing::Test
{
 public:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_SensorUpdate);
    RESET_FAKE(SDL_LockSensors);
    RESET_FAKE(SDL_UnlockSensors);
    RESET_FAKE(SDL_NumSensors);
    RESET_FAKE(SDL_SensorGetData);
    RESET_FAKE(SDL_SensorGetInstanceID);
    RESET_FAKE(SDL_SensorGetDeviceInstanceID);
    RESET_FAKE(SDL_SensorGetType);
    RESET_FAKE(SDL_SensorGetDeviceType);
    RESET_FAKE(SDL_SensorGetNonPortableType);
    RESET_FAKE(SDL_SensorGetDeviceNonPortableType);
    RESET_FAKE(SDL_SensorGetName);
    RESET_FAKE(SDL_SensorGetDeviceName);
  }

  cen::sensor_handle m_sensor{nullptr};
};

TEST_F(SensorTest, ID)
{
  const auto id [[maybe_unused]] = m_sensor.id();
  EXPECT_EQ(1, SDL_SensorGetInstanceID_fake.call_count);
}

TEST_F(SensorTest, Name)
{
  const auto name [[maybe_unused]] = m_sensor.name();
  EXPECT_EQ(1, SDL_SensorGetName_fake.call_count);
}

TEST_F(SensorTest, Type)
{
  const auto type [[maybe_unused]] = m_sensor.type();
  EXPECT_EQ(1, SDL_SensorGetType_fake.call_count);
}

TEST_F(SensorTest, NonPortableType)
{
  const auto type [[maybe_unused]] = m_sensor.non_portable_type();
  EXPECT_EQ(1, SDL_SensorGetNonPortableType_fake.call_count);
}

TEST_F(SensorTest, Data)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_SensorGetData, values.data(), cen::isize(values));

  EXPECT_FALSE(m_sensor.data<3>());
  EXPECT_TRUE(m_sensor.data<3>());
  EXPECT_EQ(2, SDL_SensorGetData_fake.call_count);
}

TEST_F(SensorTest, IDFromIndex)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_SensorGetDeviceInstanceID,
                 values.data(),
                 cen::isize(values));

  EXPECT_FALSE(cen::sensor::id(0));
  EXPECT_TRUE(cen::sensor::id(0));
  EXPECT_EQ(2, SDL_SensorGetDeviceInstanceID_fake.call_count);
}

TEST_F(SensorTest, NameFromIndex)
{
  const auto name [[maybe_unused]] = cen::sensor::name(0);
  EXPECT_EQ(1, SDL_SensorGetDeviceName_fake.call_count);
}

TEST_F(SensorTest, TypeFromIndex)
{
  const auto type [[maybe_unused]] = cen::sensor::type(0);
  EXPECT_EQ(1, SDL_SensorGetDeviceType_fake.call_count);
}

TEST_F(SensorTest, NonPortableTypeFromIndex)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_SensorGetDeviceNonPortableType,
                 values.data(),
                 cen::isize(values));

  EXPECT_FALSE(cen::sensor::non_portable_type(0));
  EXPECT_TRUE(cen::sensor::non_portable_type(0));
  EXPECT_EQ(2, SDL_SensorGetDeviceNonPortableType_fake.call_count);
}

TEST_F(SensorTest, Update)
{
  cen::sensor::update();
  EXPECT_EQ(1, SDL_SensorUpdate_fake.call_count);
}

TEST_F(SensorTest, Lock)
{
  cen::sensor::lock();
  EXPECT_EQ(1, SDL_LockSensors_fake.call_count);
}

TEST_F(SensorTest, Unlock)
{
  cen::sensor::unlock();
  EXPECT_EQ(1, SDL_UnlockSensors_fake.call_count);
}

TEST_F(SensorTest, Count)
{
  const auto count [[maybe_unused]] = cen::sensor::count();
  EXPECT_EQ(1, SDL_NumSensors_fake.call_count);
}

TEST_F(SensorTest, StreamOperator)
{
  std::cout << "COUT: " << m_sensor << '\n';
}