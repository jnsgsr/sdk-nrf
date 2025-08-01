/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// THIS FILE IS GENERATED BY ZAP
// This file is generated from clusters-Enums.h.zapt

#pragma once

#include <clusters/shared/Enums.h>
#include <cstdint>

namespace chip
{
namespace app
{
	namespace Clusters
	{
		namespace PumpConfigurationAndControl
		{

			// Enum for ControlModeEnum
			enum class ControlModeEnum : uint8_t {
				kConstantSpeed = 0x00,
				kConstantPressure = 0x01,
				kProportionalPressure = 0x02,
				kConstantFlow = 0x03,
				kConstantTemperature = 0x05,
				kAutomatic = 0x07,
				// All received enum values that are not listed above will be mapped
				// to kUnknownEnumValue. This is a helper enum value that should only
				// be used by code to process how it handles receiving and unknown
				// enum value. This specific should never be transmitted.
				kUnknownEnumValue = 4,
			};

			// Enum for OperationModeEnum
			enum class OperationModeEnum : uint8_t {
				kNormal = 0x00,
				kMinimum = 0x01,
				kMaximum = 0x02,
				kLocal = 0x03,
				// All received enum values that are not listed above will be mapped
				// to kUnknownEnumValue. This is a helper enum value that should only
				// be used by code to process how it handles receiving and unknown
				// enum value. This specific should never be transmitted.
				kUnknownEnumValue = 4,
			};

			// Bitmap for Feature
			enum class Feature : uint32_t {
				kConstantPressure = 0x1,
				kCompensatedPressure = 0x2,
				kConstantFlow = 0x4,
				kConstantSpeed = 0x8,
				kConstantTemperature = 0x10,
				kAutomatic = 0x20,
				kLocalOperation = 0x40,
			};

			// Bitmap for PumpStatusBitmap
			enum class PumpStatusBitmap : uint16_t {
				kDeviceFault = 0x1,
				kSupplyFault = 0x2,
				kSpeedLow = 0x4,
				kSpeedHigh = 0x8,
				kLocalOverride = 0x10,
				kRunning = 0x20,
				kRemotePressure = 0x40,
				kRemoteFlow = 0x80,
				kRemoteTemperature = 0x100,
			};
		} // namespace PumpConfigurationAndControl
	} // namespace Clusters
} // namespace app
} // namespace chip
