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
// This file is generated from clusters-Attributes.h.zapt

#pragma once

#include <app/ConcreteAttributePath.h>
#include <app/data-model/DecodableList.h>
#include <app/data-model/List.h>
#include <app/data-model/Nullable.h>
#include <app/util/basic-types.h>
#include <lib/core/TLV.h>
#include <lib/support/BitMask.h>

#include <clusters/shared/Attributes.h>
#include <clusters/shared/Enums.h>
#include <clusters/shared/Structs.h>

#include <clusters/TimeSynchronization/AttributeIds.h>
#include <clusters/TimeSynchronization/ClusterId.h>
#include <clusters/TimeSynchronization/Enums.h>
#include <clusters/TimeSynchronization/Structs.h>

namespace chip
{
namespace app
{
	namespace Clusters
	{
		namespace TimeSynchronization
		{
			namespace Attributes
			{

				namespace UTCTime
				{
					struct TypeInfo {
						using Type = chip::app::DataModel::Nullable<uint64_t>;
						using DecodableType = chip::app::DataModel::Nullable<uint64_t>;
						using DecodableArgType =
							const chip::app::DataModel::Nullable<uint64_t> &;

						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
						static constexpr AttributeId GetAttributeId()
						{
							return Attributes::UTCTime::Id;
						}
						static constexpr bool MustUseTimedWrite() { return false; }
					};
				} // namespace UTCTime
				namespace Granularity
				{
					struct TypeInfo {
						using Type = chip::app::Clusters::TimeSynchronization::GranularityEnum;
						using DecodableType =
							chip::app::Clusters::TimeSynchronization::GranularityEnum;
						using DecodableArgType =
							chip::app::Clusters::TimeSynchronization::GranularityEnum;

						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
						static constexpr AttributeId GetAttributeId()
						{
							return Attributes::Granularity::Id;
						}
						static constexpr bool MustUseTimedWrite() { return false; }
					};
				} // namespace Granularity
				namespace TimeSource
				{
					struct TypeInfo {
						using Type = chip::app::Clusters::TimeSynchronization::TimeSourceEnum;
						using DecodableType =
							chip::app::Clusters::TimeSynchronization::TimeSourceEnum;
						using DecodableArgType =
							chip::app::Clusters::TimeSynchronization::TimeSourceEnum;

						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
						static constexpr AttributeId GetAttributeId()
						{
							return Attributes::TimeSource::Id;
						}
						static constexpr bool MustUseTimedWrite() { return false; }
					};
				} // namespace TimeSource
				namespace TrustedTimeSource
				{
					struct TypeInfo {
						using Type = chip::app::DataModel::Nullable<
							chip::app::Clusters::TimeSynchronization::Structs::
								TrustedTimeSourceStruct::Type>;
						using DecodableType = chip::app::DataModel::Nullable<
							chip::app::Clusters::TimeSynchronization::Structs::
								TrustedTimeSourceStruct::DecodableType>;
						using DecodableArgType = const chip::app::DataModel::Nullable<
							chip::app::Clusters::TimeSynchronization::Structs::
								TrustedTimeSourceStruct::DecodableType> &;

						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
						static constexpr AttributeId GetAttributeId()
						{
							return Attributes::TrustedTimeSource::Id;
						}
						static constexpr bool MustUseTimedWrite() { return false; }
					};
				} // namespace TrustedTimeSource
				namespace DefaultNTP
				{
					struct TypeInfo {
						using Type = chip::app::DataModel::Nullable<chip::CharSpan>;
						using DecodableType = chip::app::DataModel::Nullable<chip::CharSpan>;
						using DecodableArgType =
							const chip::app::DataModel::Nullable<chip::CharSpan> &;

						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
						static constexpr AttributeId GetAttributeId()
						{
							return Attributes::DefaultNTP::Id;
						}
						static constexpr bool MustUseTimedWrite() { return false; }
						static constexpr size_t MaxLength() { return 128; }
					};
				} // namespace DefaultNTP
				namespace TimeZone
				{
					struct TypeInfo {
						using Type = chip::app::DataModel::List<
							const chip::app::Clusters::TimeSynchronization::Structs::
								TimeZoneStruct::Type>;
						using DecodableType = chip::app::DataModel::DecodableList<
							chip::app::Clusters::TimeSynchronization::Structs::
								TimeZoneStruct::DecodableType>;
						using DecodableArgType = const chip::app::DataModel::DecodableList<
							chip::app::Clusters::TimeSynchronization::Structs::
								TimeZoneStruct::DecodableType> &;

						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
						static constexpr AttributeId GetAttributeId()
						{
							return Attributes::TimeZone::Id;
						}
						static constexpr bool MustUseTimedWrite() { return false; }
					};
				} // namespace TimeZone
				namespace DSTOffset
				{
					struct TypeInfo {
						using Type = chip::app::DataModel::List<
							const chip::app::Clusters::TimeSynchronization::Structs::
								DSTOffsetStruct::Type>;
						using DecodableType = chip::app::DataModel::DecodableList<
							chip::app::Clusters::TimeSynchronization::Structs::
								DSTOffsetStruct::DecodableType>;
						using DecodableArgType = const chip::app::DataModel::DecodableList<
							chip::app::Clusters::TimeSynchronization::Structs::
								DSTOffsetStruct::DecodableType> &;

						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
						static constexpr AttributeId GetAttributeId()
						{
							return Attributes::DSTOffset::Id;
						}
						static constexpr bool MustUseTimedWrite() { return false; }
					};
				} // namespace DSTOffset
				namespace LocalTime
				{
					struct TypeInfo {
						using Type = chip::app::DataModel::Nullable<uint64_t>;
						using DecodableType = chip::app::DataModel::Nullable<uint64_t>;
						using DecodableArgType =
							const chip::app::DataModel::Nullable<uint64_t> &;

						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
						static constexpr AttributeId GetAttributeId()
						{
							return Attributes::LocalTime::Id;
						}
						static constexpr bool MustUseTimedWrite() { return false; }
					};
				} // namespace LocalTime
				namespace TimeZoneDatabase
				{
					struct TypeInfo {
						using Type =
							chip::app::Clusters::TimeSynchronization::TimeZoneDatabaseEnum;
						using DecodableType =
							chip::app::Clusters::TimeSynchronization::TimeZoneDatabaseEnum;
						using DecodableArgType =
							chip::app::Clusters::TimeSynchronization::TimeZoneDatabaseEnum;

						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
						static constexpr AttributeId GetAttributeId()
						{
							return Attributes::TimeZoneDatabase::Id;
						}
						static constexpr bool MustUseTimedWrite() { return false; }
					};
				} // namespace TimeZoneDatabase
				namespace NTPServerAvailable
				{
					struct TypeInfo {
						using Type = bool;
						using DecodableType = bool;
						using DecodableArgType = bool;

						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
						static constexpr AttributeId GetAttributeId()
						{
							return Attributes::NTPServerAvailable::Id;
						}
						static constexpr bool MustUseTimedWrite() { return false; }
					};
				} // namespace NTPServerAvailable
				namespace TimeZoneListMaxSize
				{
					struct TypeInfo {
						using Type = uint8_t;
						using DecodableType = uint8_t;
						using DecodableArgType = uint8_t;

						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
						static constexpr AttributeId GetAttributeId()
						{
							return Attributes::TimeZoneListMaxSize::Id;
						}
						static constexpr bool MustUseTimedWrite() { return false; }
					};
				} // namespace TimeZoneListMaxSize
				namespace DSTOffsetListMaxSize
				{
					struct TypeInfo {
						using Type = uint8_t;
						using DecodableType = uint8_t;
						using DecodableArgType = uint8_t;

						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
						static constexpr AttributeId GetAttributeId()
						{
							return Attributes::DSTOffsetListMaxSize::Id;
						}
						static constexpr bool MustUseTimedWrite() { return false; }
					};
				} // namespace DSTOffsetListMaxSize
				namespace SupportsDNSResolve
				{
					struct TypeInfo {
						using Type = bool;
						using DecodableType = bool;
						using DecodableArgType = bool;

						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
						static constexpr AttributeId GetAttributeId()
						{
							return Attributes::SupportsDNSResolve::Id;
						}
						static constexpr bool MustUseTimedWrite() { return false; }
					};
				} // namespace SupportsDNSResolve
				namespace GeneratedCommandList
				{
					struct TypeInfo
						: public Clusters::Globals::Attributes::GeneratedCommandList::TypeInfo {
						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
					};
				} // namespace GeneratedCommandList
				namespace AcceptedCommandList
				{
					struct TypeInfo
						: public Clusters::Globals::Attributes::AcceptedCommandList::TypeInfo {
						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
					};
				} // namespace AcceptedCommandList
				namespace AttributeList
				{
					struct TypeInfo
						: public Clusters::Globals::Attributes::AttributeList::TypeInfo {
						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
					};
				} // namespace AttributeList
				namespace FeatureMap
				{
					struct TypeInfo : public Clusters::Globals::Attributes::FeatureMap::TypeInfo {
						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
					};
				} // namespace FeatureMap
				namespace ClusterRevision
				{
					struct TypeInfo
						: public Clusters::Globals::Attributes::ClusterRevision::TypeInfo {
						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}
					};
				} // namespace ClusterRevision

				struct TypeInfo {
					struct DecodableType {
						static constexpr ClusterId GetClusterId()
						{
							return Clusters::TimeSynchronization::Id;
						}

						CHIP_ERROR Decode(TLV::TLVReader &reader,
								  const ConcreteAttributePath &path);

						Attributes::UTCTime::TypeInfo::DecodableType UTCTime;
						Attributes::Granularity::TypeInfo::DecodableType granularity =
							static_cast<chip::app::Clusters::TimeSynchronization::
									    GranularityEnum>(0);
						Attributes::TimeSource::TypeInfo::DecodableType timeSource = static_cast<
							chip::app::Clusters::TimeSynchronization::TimeSourceEnum>(0);
						Attributes::TrustedTimeSource::TypeInfo::DecodableType trustedTimeSource;
						Attributes::DefaultNTP::TypeInfo::DecodableType defaultNTP;
						Attributes::TimeZone::TypeInfo::DecodableType timeZone;
						Attributes::DSTOffset::TypeInfo::DecodableType DSTOffset;
						Attributes::LocalTime::TypeInfo::DecodableType localTime;
						Attributes::TimeZoneDatabase::TypeInfo::DecodableType timeZoneDatabase =
							static_cast<chip::app::Clusters::TimeSynchronization::
									    TimeZoneDatabaseEnum>(0);
						Attributes::NTPServerAvailable::TypeInfo::DecodableType
							NTPServerAvailable = static_cast<bool>(0);
						Attributes::TimeZoneListMaxSize::TypeInfo::DecodableType
							timeZoneListMaxSize = static_cast<uint8_t>(0);
						Attributes::DSTOffsetListMaxSize::TypeInfo::DecodableType
							DSTOffsetListMaxSize = static_cast<uint8_t>(0);
						Attributes::SupportsDNSResolve::TypeInfo::DecodableType
							supportsDNSResolve = static_cast<bool>(0);
						Attributes::GeneratedCommandList::TypeInfo::DecodableType
							generatedCommandList;
						Attributes::AcceptedCommandList::TypeInfo::DecodableType
							acceptedCommandList;
						Attributes::AttributeList::TypeInfo::DecodableType attributeList;
						Attributes::FeatureMap::TypeInfo::DecodableType featureMap =
							static_cast<uint32_t>(0);
						Attributes::ClusterRevision::TypeInfo::DecodableType clusterRevision =
							static_cast<uint16_t>(0);
					};
				};
			} // namespace Attributes
		} // namespace TimeSynchronization
	} // namespace Clusters
} // namespace app
} // namespace chip
