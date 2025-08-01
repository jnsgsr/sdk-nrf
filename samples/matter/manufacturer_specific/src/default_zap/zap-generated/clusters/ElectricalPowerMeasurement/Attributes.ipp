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
// This file is generated from clusters-Attributes.ipp.zapt

#include <clusters/ElectricalPowerMeasurement/Attributes.h>

#include <app/data-model/Decode.h>
#include <app/data-model/WrappedStructEncoder.h>

namespace chip
{
namespace app
{
	namespace Clusters
	{
		namespace ElectricalPowerMeasurement
		{
			namespace Attributes
			{
				CHIP_ERROR TypeInfo::DecodableType::Decode(TLV::TLVReader &reader,
									   const ConcreteAttributePath &path)
				{
					switch (path.mAttributeId) {
					case Attributes::PowerMode::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, powerMode);
					case Attributes::NumberOfMeasurementTypes::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, numberOfMeasurementTypes);
					case Attributes::Accuracy::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, accuracy);
					case Attributes::Ranges::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, ranges);
					case Attributes::Voltage::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, voltage);
					case Attributes::ActiveCurrent::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, activeCurrent);
					case Attributes::ReactiveCurrent::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, reactiveCurrent);
					case Attributes::ApparentCurrent::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, apparentCurrent);
					case Attributes::ActivePower::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, activePower);
					case Attributes::ReactivePower::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, reactivePower);
					case Attributes::ApparentPower::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, apparentPower);
					case Attributes::RMSVoltage::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, RMSVoltage);
					case Attributes::RMSCurrent::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, RMSCurrent);
					case Attributes::RMSPower::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, RMSPower);
					case Attributes::Frequency::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, frequency);
					case Attributes::HarmonicCurrents::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, harmonicCurrents);
					case Attributes::HarmonicPhases::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, harmonicPhases);
					case Attributes::PowerFactor::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, powerFactor);
					case Attributes::NeutralCurrent::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, neutralCurrent);
					case Attributes::GeneratedCommandList::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, generatedCommandList);
					case Attributes::AcceptedCommandList::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, acceptedCommandList);
					case Attributes::AttributeList::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, attributeList);
					case Attributes::FeatureMap::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, featureMap);
					case Attributes::ClusterRevision::TypeInfo::GetAttributeId():
						return DataModel::Decode(reader, clusterRevision);
					default:
						return CHIP_NO_ERROR;
					}
				}
			} // namespace Attributes
		} // namespace ElectricalPowerMeasurement
	} // namespace Clusters
} // namespace app
} // namespace chip
