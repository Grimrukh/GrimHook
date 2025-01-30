﻿#pragma once

#include <array>
#include <cstdint>
#include <map>
#include <string>
#include <variant>
#include <vector>

#include "GrimHook/Collections.h"
#include "GrimHookER/Export.h"
#include "Entry.h"
#include "EntryParam.h"
#include "EntryReference.h"
#include "Shape.h"

namespace GrimHookER::Maps::MapStudio
{
    using GrimHook::Vector3;

    enum class RegionType : uint32_t
    {
        InvasionPoint = 1,
        EnvironmentMapPoint = 2,
        Sound = 4,
        VFX = 5,
        WindVFX = 6,
        SpawnPoint = 8,
        Message = 9,
        EnvironmentMapEffectBox = 17,
        WindArea = 18,
        Connection = 21,
        PatrolRoute22 = 22,
        BuddySummonPoint = 26,
        MufflingBox = 28,
        MufflingPortal = 29,
        OtherSound = 30,
        MufflingPlane = 31,
        PatrolRoute = 32,  // NOTE: be wary of Event subtype with same name
        MapPoint = 33,
        WeatherOverride = 35,
        AutoDrawGroupPoint = 36,
        GroupDefeatReward = 37,
        MapPointDiscoveryOverride = 38,
        MapPointParticipationOverride = 39,
        Hitset = 40,
        FastTravelRestriction = 41,
        WeatherCreateAssetPoint = 42,
        PlayArea = 43,
        EnvironmentMapOutput = 44,
        MountJump = 46,
        Dummy = 48,
        FallPreventionRemoval = 49,
        NavmeshCutting = 50,
        MapNameOverride = 51,
        MountJumpFall = 52,
        HorseRideOverride = 53,
        Other = 0xFFFFFFFF,
    };

    inline std::map<RegionType, std::string> regionTypeNames =
    {
        {RegionType::InvasionPoint, "InvasionPoint"},
        {RegionType::EnvironmentMapPoint, "EnvironmentMapPoint"},
        {RegionType::Sound, "Sound"},
        {RegionType::VFX, "VFX"},
        {RegionType::WindVFX, "WindVFX"},
        {RegionType::SpawnPoint, "SpawnPoint"},
        {RegionType::Message, "Message"},
        {RegionType::EnvironmentMapEffectBox, "EnvironmentMapEffectBox"},
        {RegionType::WindArea, "WindArea"},
        {RegionType::Connection, "Connection"},
        {RegionType::PatrolRoute22, "PatrolRoute22"},
        {RegionType::BuddySummonPoint, "BuddySummonPoint"},
        {RegionType::MufflingBox, "MufflingBox"},
        {RegionType::MufflingPortal, "MufflingPortal"},
        {RegionType::OtherSound, "OtherSound"},
        {RegionType::MufflingPlane, "MufflingPlane"},
        {RegionType::PatrolRoute, "PatrolRoute"},
        {RegionType::MapPoint, "MapPoint"},
        {RegionType::WeatherOverride, "WeatherOverride"},
        {RegionType::AutoDrawGroupPoint, "AutoDrawGroupPoint"},
        {RegionType::GroupDefeatReward, "GroupDefeatReward"},
        {RegionType::MapPointDiscoveryOverride, "MapPointDiscoveryOverride"},
        {RegionType::MapPointParticipationOverride, "MapPointParticipationOverride"},
        {RegionType::Hitset, "Hitset"},
        {RegionType::FastTravelRestriction, "FastTravelRestriction"},
        {RegionType::WeatherCreateAssetPoint, "WeatherCreateAssetPoint"},
        {RegionType::PlayArea, "PlayArea"},
        {RegionType::EnvironmentMapOutput, "EnvironmentMapOutput"},
        {RegionType::MountJump, "MountJump"},
        {RegionType::Dummy, "Dummy"},
        {RegionType::FallPreventionRemoval, "FallPreventionRemoval"},
        {RegionType::NavmeshCutting, "NavmeshCutting"},
        {RegionType::MapNameOverride, "MapNameOverride"},
        {RegionType::MountJumpFall, "MountJumpFall"},
        {RegionType::HorseRideOverride, "HorseRideOverride"},
        {RegionType::Other, "OtherRegion"},
    };

    class GRIMHOOKER_API Region : public EntityEntry
    {
    public:
        using EnumType = RegionType;

        explicit Region(const std::string& name) : EntityEntry(name) {}

        /// @brief Copy constructor that clones a new unique `Shape` (if present).
        Region(const Region& other) : EntityEntry(other.m_name)
        {
            // Copy shape if present.
            shape = other.shape ? other.shape->Clone() : nullptr;
            translate = other.translate;
            rotate = other.rotate;
            hUnk40 = other.hUnk40;
            eventLayer = other.eventLayer;
            unkShortsA = std::vector(other.unkShortsA);
            unkShortsB = std::vector(other.unkShortsB);
            attachedPart = other.attachedPart;
            attachedPartIndex = other.attachedPartIndex;
            m_entityId = other.m_entityId;
            dUnk08 = other.dUnk08;
            mapId = other.mapId;
            eUnk04 = other.eUnk04;
            eUnk0C = other.eUnk0C;
        }

        [[nodiscard]] virtual RegionType GetType() const = 0;

        /// @brief Get type enum `ShapeType` of this Region's shape.
        [[nodiscard]] ShapeType GetShapeType() const { return shape == nullptr ? ShapeType::PointShape : shape->GetType(); }

        /// @brief Set this region's shape to  Creates a new instance of given shape type, which is then returned for caller modification.
        // Previous shape will be discarded (as a unique_ptr).
        std::unique_ptr<Shape>& SetShapeType(ShapeType shapeType);

        [[nodiscard]] std::string GetShapeTypeName() const { return shapeTypeNames[GetShapeType()]; }

        [[nodiscard]] std::unique_ptr<Shape>& GetShape() { return shape; }

        [[nodiscard]] Vector3 GetTranslate() const { return translate; }
        void SetTranslate(const Vector3& translate) { this->translate = translate; }

        [[nodiscard]] Vector3 GetRotate() const { return rotate; }
        void SetRotate(const Vector3& rotate) { this->rotate = rotate; }

        [[nodiscard]] int32_t GetHUnk40() const { return hUnk40; }
        void SetHUnk40(const int32_t hUnk40) { this->hUnk40 = hUnk40; }

        [[nodiscard]] int32_t GetEventLayer() const { return eventLayer; }
        void SetEventLayer(const int32_t eventLayer) { this->eventLayer = eventLayer; }

        [[nodiscard]] Part* GetAttachedPart() const { return attachedPart.Get(); }
        void SetAttachedPart(Part* const part) { this->attachedPart.Set(part); }
        void SetAttachedPart(const std::unique_ptr<Part>& part) { this->attachedPart.Set(part); }

        [[nodiscard]] uint8_t GetDUnk08() const { return dUnk08; }
        void SetDUnk08(const uint8_t dUnk08) { this->dUnk08 = dUnk08; }

        [[nodiscard]] int32_t GetMapId() const { return mapId; }
        void SetMapId(const int32_t mapId) { this->mapId = mapId; }

        [[nodiscard]] int32_t GetEUnk04() const { return eUnk04; }
        void SetEUnk04(const int32_t eUnk04) { this->eUnk04 = eUnk04; }

        [[nodiscard]] int32_t GetEUnk0C() const { return eUnk0C; }
        void SetEUnk0C(const int32_t eUnk0C) { this->eUnk0C = eUnk0C; }

        void Deserialize(std::ifstream& stream) override;
        void Serialize(std::ofstream& stream, int supertypeIndex, int subtypeIndex) const override;

        virtual void DeserializeEntryReferences(const std::vector<Region*>& regions, const std::vector<Part*>& parts);
        virtual void SerializeEntryIndices(const std::vector<Region*>& regions, const std::vector<Part*>& parts);

        explicit operator std::string() const
        {
            return regionTypeNames[GetType()] + " <" + GetShapeTypeName() + "> " + m_name;
        }

    protected:

        /// @brief Stores child `Region` references for `Composite` shape (and each of their `unk04` values).
        struct CompositeShapeReferences
        {
            std::array<EntryReference<Region>, 8> regionReferences{};  // null references
            std::array<int, 8> regionIndices{};  // filled with -1 in constructor
            std::array<int, 8> unk04s{};  // default 0 is good

            /// @brief Default region indices are -1 (indicates unused).
            explicit CompositeShapeReferences()
            {
                regionIndices.fill(-1);
            }

            void SetReferences(const std::vector<Region*>& regions)
            {
                for (int i = 0; i < 8; ++i)
                    regionReferences[i].SetFromIndex(regions, regionIndices[i]);
            }

            void SetIndices(const Entry* sourceEntry, const std::vector<Region*>& regions)
            {
                for (int i = 0; i < 8; ++i)
                    regionIndices[i] = regionReferences[i].ToIndex(sourceEntry, regions);
            }
        };

        /// @brief `Shape` of this region. Must be a pointer for polymorphism. `nullptr` means a `Point` shape.
        std::unique_ptr<Shape> shape = nullptr;

        /// @brief Optional `CompositeShapeReferences` to store `Composite` type shape children and their `unk04` value.
        /// Stored here, rather than in `Composite`, to make use of safe entry referencing system.
        std::unique_ptr<CompositeShapeReferences> compositeChildren = nullptr;

        Vector3 translate = Vector3{};
        Vector3 rotate = Vector3{};  // Euler angles in radians
        int32_t hUnk40 = 0;
        int32_t eventLayer = -1;
        std::vector<int16_t> unkShortsA{};
        std::vector<int16_t> unkShortsB{};

        EntryReference<Part> attachedPart;
        int32_t attachedPartIndex = -1;
        // `entityId` defined in parent class.
        uint8_t dUnk08 = 0;

        int32_t mapId = 0;
        int32_t eUnk04 = 0;
        int32_t eUnk0C = 0;

        virtual bool DeserializeSubtypeData(std::ifstream& stream) { return false; }
        virtual bool SerializeSubtypeData(std::ofstream& stream) const { return false; }
    };

    class GRIMHOOKER_API InvasionPointRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::InvasionPoint;

        explicit InvasionPointRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetPriority() const { return priority; }
        void SetPriority(const int newPriority) { priority = newPriority; }

    private:
        int priority = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };

    class GRIMHOOKER_API EnvironmentMapPointRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::EnvironmentMapPoint;

        explicit EnvironmentMapPointRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] float GetSUnk00() const { return sUnk00; }
        void SetSUnk00(const float unk00) { this->sUnk00 = unk00; }
        [[nodiscard]] int GetSUnk04() const { return sUnk04; }
        void SetSUnk04(const int unk04) { this->sUnk04 = unk04; }
        [[nodiscard]] bool IsSUnk0D() const { return sUnk0D; }
        void SetSUnk0D(const bool unk0D) { this->sUnk0D = unk0D; }
        [[nodiscard]] bool IsSUnk0E() const { return sUnk0E; }
        void SetSUnk0E(const bool unk0E) { this->sUnk0E = unk0E; }
        [[nodiscard]] bool IsSUnk0F() const { return sUnk0F; }
        void SetSUnk0F(const bool unk0F) { this->sUnk0F = unk0F; }
        [[nodiscard]] float GetSUnk10() const { return sUnk10; }
        void SetSUnk10(const float unk10) { this->sUnk10 = unk10; }
        [[nodiscard]] float GetSUnk14() const { return sUnk14; }
        void SetSUnk14(const float unk14) { this->sUnk14 = unk14; }
        [[nodiscard]] int GetSMapId() const { return sMapId; }
        void SetSMapId(const int mapId) { this->sMapId = mapId; }
        [[nodiscard]] int GetSUnk20() const { return sUnk20; }
        void SetSUnk20(const int unk20) { this->sUnk20 = unk20; }
        [[nodiscard]] int GetSUnk24() const { return sUnk24; }
        void SetSUnk24(const int unk24) { this->sUnk24 = unk24; }
        [[nodiscard]] int GetSUnk28() const { return sUnk28; }
        void SetSUnk28(const int unk28) { this->sUnk28 = unk28; }
        [[nodiscard]] uint8_t GetSUnk2C() const { return sUnk2C; }
        void SetSUnk2C(const uint8_t unk2C) { this->sUnk2C = unk2C; }
        [[nodiscard]] uint8_t GetSUnk2D() const { return sUnk2D; }
        void SetSUnk2D(const uint8_t unk2D) { this->sUnk2D = unk2D; }

    private:
        float sUnk00 = 0.0f;
        int sUnk04 = 0;
        bool sUnk0D = false;
        bool sUnk0E = false;
        bool sUnk0F = false;
        float sUnk10 = 0.0f;
        float sUnk14 = 0.0f;
        int sMapId = 0;
        int sUnk20 = 0;
        int sUnk24 = 0;
        int sUnk28 = 0;
        uint8_t sUnk2C = 0;
        uint8_t sUnk2D = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };

    class GRIMHOOKER_API SoundRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::Sound;

        explicit SoundRegion(const std::string& name) : Region(name)
        {
            childRegionsIndices.fill(-1);
        }

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetSoundType() const { return soundType; }
        void SetSoundType(const int soundType) { this->soundType = soundType; }

        [[nodiscard]] int GetSoundId() const { return soundId; }
        void SetSoundId(const int soundId) { this->soundId = soundId; }

        [[nodiscard]] Region* GetChildRegionAtIndex(const int index) const { return childRegions[index].Get(); }
        void SetChildRegionAtIndex(const int index, Region* const region) { childRegions[index].Set(region); }
        void SetChildRegionAtIndex(const int index, const std::unique_ptr<Region>& region) { childRegions[index].Set(region); }

        [[nodiscard]] bool IsSUnk49() const { return sUnk49; }
        void SetSUnk49(const bool sUnk49) { this->sUnk49 = sUnk49; }

        void DeserializeEntryReferences(const std::vector<Region*>& regions, const std::vector<Part*>& parts) override;
        void SerializeEntryIndices(const std::vector<Region*>& regions, const std::vector<Part*>& parts) override;

    private:
        int soundType = 0;
        int soundId = 0;
        std::array<EntryReference<Region>, 16> childRegions{};
        std::array<int, 16> childRegionsIndices{};
        bool sUnk49 = false;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };

    class GRIMHOOKER_API VFXRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::VFX;

        explicit VFXRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetEffectId() const { return effectId; }
        void SetEffectId(const int effectId) { this->effectId = effectId; }

        [[nodiscard]] int GetSUnk04() const { return sUnk04; }
        void SetSUnk04(const int unk04) { this->sUnk04 = unk04; }

    private:
        int effectId = 0;
        int sUnk04 = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;};

    class GRIMHOOKER_API WindVFXRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::WindVFX;

        explicit WindVFXRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetEffectId() const { return effectId; }
        void SetEffectId(const int effectId) { this->effectId = effectId; }

        [[nodiscard]] Region* GetWindRegion() const { return windRegion.Get(); }
        void SetWindRegion(Region* const windRegion) { this->windRegion.Set(windRegion); }
        void SetWindRegion(const std::unique_ptr<Region>& windRegion) { this->windRegion.Set(windRegion); }

        [[nodiscard]] float GetSUnk08() const { return sUnk08; }
        void SetSUnk08(const float unk08) { this->sUnk08 = unk08; }

        void DeserializeEntryReferences(const std::vector<Region*>& regions, const std::vector<Part*>& parts) override;
        void SerializeEntryIndices(const std::vector<Region*>& regions, const std::vector<Part*>& parts) override;

    private:
        int effectId = 0;
        EntryReference<Region> windRegion;
        int windRegionIndex = -1;
        float sUnk08 = 0.0f;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };


    class GRIMHOOKER_API SpawnPointRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::SpawnPoint;

        explicit SpawnPointRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

    private:
        // No actual data (just pads).

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };

    class GRIMHOOKER_API MessageRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::Message;

        explicit MessageRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int16_t GetMessageId() const { return messageId; }
        void SetMessageId(const int16_t messageId) { this->messageId = messageId; }
        [[nodiscard]] int16_t GetSUnk02() const { return sUnk02; }
        void SetSUnk02(const int16_t sUnk02) { this->sUnk02 = sUnk02; }
        [[nodiscard]] bool IsHidden() const { return hidden; }
        void SetHidden(const bool hidden) { this->hidden = hidden; }
        [[nodiscard]] int GetSUnk08() const { return sUnk08; }
        void SetSUnk08(const int sUnk08) { this->sUnk08 = sUnk08; }
        [[nodiscard]] int GetSUnk0C() const { return sUnk0C; }
        void SetSUnk0C(const int sUnk0C) { this->sUnk0C = sUnk0C; }
        [[nodiscard]] uint32_t GetEnableEventFlagId() const { return enableEventFlagId; }
        void SetEnableEventFlagId(const uint32_t enableEventFlagId) { this->enableEventFlagId = enableEventFlagId; }
        [[nodiscard]] int GetCharacterModelName() const { return characterModelName; }
        void SetCharacterModelName(const int characterModelName) { this->characterModelName = characterModelName; }
        [[nodiscard]] int GetCharacterId() const { return characterId; }
        void SetCharacterId(const int characterId) { this->characterId = characterId; }
        [[nodiscard]] int GetAnimationId() const { return animationId; }
        void SetAnimationId(const int animationId) { this->animationId = animationId; }
        [[nodiscard]] int GetPlayerId() const { return playerId; }
        void SetPlayerId(const int playerId) { this->playerId = playerId; }
    private:
        int16_t messageId = 0;
        int16_t sUnk02 = 0;
        bool hidden = false;  // stored as 32-bit int
        int sUnk08 = 0;
        int sUnk0C = 0;
        uint32_t enableEventFlagId = 0;
        int characterModelName = 0;  // TODO: Is this really a 'name ID' or just the ID? e.g. 1234 -> 'c1234'
        int characterId = 0; // NpcParam
        int animationId = 0;
        int playerId = 0; // CharaInitParam

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;  };

    class GRIMHOOKER_API EnvironmentMapEffectBoxRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::EnvironmentMapEffectBox;

        explicit EnvironmentMapEffectBoxRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] float GetEnableDist() const { return enableDist; }
        void SetEnableDist(const float enableDist) { this->enableDist = enableDist; }
        [[nodiscard]] float GetTransitionDist() const { return transitionDist; }
        void SetTransitionDist(const float transitionDist) { this->transitionDist = transitionDist; }
        [[nodiscard]] int GetSUnk08() const { return sUnk08; }
        void SetSUnk08(const int sUnk08) { this->sUnk08 = sUnk08; }
        [[nodiscard]] int GetSUnk09() const { return sUnk09; }
        void SetSUnk09(const int sUnk09) { this->sUnk09 = sUnk09; }
        [[nodiscard]] int16_t GetSUnk0A() const { return sUnk0A; }
        void SetSUnk0A(const int16_t sUnk0A) { this->sUnk0A = sUnk0A; }
        [[nodiscard]] float GetSUnk24() const { return sUnk24; }
        void SetSUnk24(const float sUnk24) { this->sUnk24 = sUnk24; }
        [[nodiscard]] float GetSUnk28() const { return sUnk28; }
        void SetSUnk28(const float sUnk28) { this->sUnk28 = sUnk28; }
        [[nodiscard]] int16_t GetSUnk2C() const { return sUnk2C; }
        void SetSUnk2C(const int16_t sUnk2C) { this->sUnk2C = sUnk2C; }
        [[nodiscard]] bool IsSUnk2E() const { return sUnk2E; }
        void SetSUnk2E(const bool sUnk2E) { this->sUnk2E = sUnk2E; }
        [[nodiscard]] bool IsSUnk2F() const { return sUnk2f; }
        void SetSUnk2F(const bool sUnk2F) { sUnk2f = sUnk2F; }
        [[nodiscard]] int16_t GetSUnk30() const { return sUnk30; }
        void SetSUnk30(const int16_t sUnk30) { this->sUnk30 = sUnk30; }
        [[nodiscard]] bool IsSUnk33() const { return sUnk33; }
        void SetSUnk33(const bool sUnk33) { this->sUnk33 = sUnk33; }
        [[nodiscard]] int16_t GetSUnk34() const { return sUnk34; }
        void SetSUnk34(const int16_t sUnk34) { this->sUnk34 = sUnk34; }
        [[nodiscard]] int16_t GetSUnk36() const { return sUnk36; }
        void SetSUnk36(const int16_t sUnk36) { this->sUnk36 = sUnk36; }

    private:
        float enableDist = 0.0f;
        float transitionDist = 0.0f;
        uint8_t sUnk08 = 0;
        uint8_t sUnk09 = 0;
        int16_t sUnk0A = 0;
        float sUnk24 = 0.0f;
        float sUnk28 = 0.0f;
        int16_t sUnk2C = 0;
        bool sUnk2E = false;
        bool sUnk2f = false;
        int16_t sUnk30 = 0;
        bool sUnk33 = false;
        int16_t sUnk34 = 0;
        int16_t sUnk36 = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };

    class GRIMHOOKER_API WindAreaRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::WindArea;

        explicit WindAreaRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        // No subtype data read/write, not even pads.
    };

    class GRIMHOOKER_API ConnectionRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::Connection;

        explicit ConnectionRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] std::array<int8_t, 4> GetTargetMapId() const { return targetMapId; }
        void SetTargetMapId(const std::array<int8_t, 4>& targetMapId) { this->targetMapId = targetMapId; }

    private:
        std::array<int8_t, 4> targetMapId = {0, 0, 0, 0};  // map reference, e.g. {10, 0, 0, 0} for 'm10_00_00_00'

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };

    class GRIMHOOKER_API PatrolRoute22Region final : public Region
    {
    public:
        static constexpr auto Type = RegionType::PatrolRoute22;

        explicit PatrolRoute22Region(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }
    private:
        // No subtype data (just pads).
        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;

    };

    class GRIMHOOKER_API BuddySummonPointRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::BuddySummonPoint;

        explicit BuddySummonPointRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }
    private:
        // No subtype data (just pads).
        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };

    class GRIMHOOKER_API MufflingBoxRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::MufflingBox;

        explicit MufflingBoxRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetSUnk00() const { return sUnk00; }
        void SetSUnk00(const int sUnk00) { this->sUnk00 = sUnk00; }
        [[nodiscard]] float GetSUnk24() const { return sUnk24; }
        void SetSUnk24(const float sUnk24) { this->sUnk24 = sUnk24; }
        [[nodiscard]] float GetSUnk34() const { return sUnk34; }
        void SetSUnk34(const float sUnk34) { this->sUnk34 = sUnk34; }
        [[nodiscard]] float GetSUnk3C() const { return sUnk3c; }
        void SetSUnk3C(const float sUnk3C) { sUnk3c = sUnk3C; }
        [[nodiscard]] float GetSUnk40() const { return sUnk40; }
        void SetSUnk40(const float sUnk40) { this->sUnk40 = sUnk40; }
        [[nodiscard]] float GetSUnk44() const { return sUnk44; }
        void SetSUnk44(const float sUnk44) { this->sUnk44 = sUnk44; }

    private:
        int sUnk00 = 0;
        float sUnk24 = 0.0f;
        float sUnk34 = 0.0f;
        float sUnk3c = 0.0f;
        float sUnk40 = 0.0f;
        float sUnk44 = 0.0f;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };

    class GRIMHOOKER_API MufflingPortalRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::MufflingPortal;

        explicit MufflingPortalRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetSUnk00() const { return sUnk00; }
        void SetSUnk00(const int sUnk00) { this->sUnk00 = sUnk00; }

    private:
        int sUnk00 = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };

    class GRIMHOOKER_API OtherSoundRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::OtherSound;

        explicit OtherSoundRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] uint8_t GetSUnk00() const { return sUnk00; }
        void SetSUnk00(const uint8_t sUnk00) { this->sUnk00 = sUnk00; }
        [[nodiscard]] uint8_t GetSUnk01() const { return sUnk01; }
        void SetSUnk01(const uint8_t sUnk01) { this->sUnk01 = sUnk01; }
        [[nodiscard]] uint8_t GetSUnk02() const { return sUnk02; }
        void SetSUnk02(const uint8_t sUnk02) { this->sUnk02 = sUnk02; }
        [[nodiscard]] uint8_t GetSUnk03() const { return sUnk03; }
        void SetSUnk03(const uint8_t sUnk03) { this->sUnk03 = sUnk03; }
        [[nodiscard]] int GetSUnk04() const { return sUnk04; }
        void SetSUnk04(const int sUnk04) { this->sUnk04 = sUnk04; }
        [[nodiscard]] short GetSUnk08() const { return sUnk08; }
        void SetSUnk08(const short sUnk08) { this->sUnk08 = sUnk08; }
        [[nodiscard]] short GetSUnk0A() const { return sUnk0a; }
        void SetSUnk0A(const short sUnk0A) { sUnk0a = sUnk0A; }
        [[nodiscard]] uint8_t GetSUnk0C() const { return sUnk0c; }
        void SetSUnk0C(const uint8_t sUnk0C) { sUnk0c = sUnk0C; }

    private:
        uint8_t sUnk00 = 0;
        uint8_t sUnk01 = 0;
        uint8_t sUnk02 = 0;
        uint8_t sUnk03 = 0;
        int sUnk04 = 0;
        short sUnk08 = 0;
        short sUnk0a = 0;
        uint8_t sUnk0c = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };

    class GRIMHOOKER_API MufflingPlaneRegion final : public Region
    {
        // No subtype data at all.
    public:
        static constexpr auto Type = RegionType::MufflingPlane;

        explicit MufflingPlaneRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }
    };

    class GRIMHOOKER_API PatrolRouteRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::PatrolRoute;

        explicit PatrolRouteRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetSUnk00() const { return sUnk00; }
        void SetSUnk00(const int sUnk00) { this->sUnk00 = sUnk00; }

    private:
        int sUnk00 = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };

    class GRIMHOOKER_API MapPointRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::MapPoint;

        explicit MapPointRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetSUnk00() const { return sUnk00; }
        void SetSUnk00(const int sUnk00) { this->sUnk00 = sUnk00; }
        [[nodiscard]] int GetSUnk04() const { return sUnk04; }
        void SetSUnk04(const int sUnk04) { this->sUnk04 = sUnk04; }
        [[nodiscard]] float GetSUnk08() const { return sUnk08; }
        void SetSUnk08(const float sUnk08) { this->sUnk08 = sUnk08; }
        [[nodiscard]] float GetSUnk0C() const { return sUnk0C; }
        void SetSUnk0C(const float sUnk0C) { this->sUnk0C = sUnk0C; }
        [[nodiscard]] float GetSUnk14() const { return sUnk14; }
        void SetSUnk14(const float sUnk14) { this->sUnk14 = sUnk14; }
        [[nodiscard]] float GetSUnk18() const { return sUnk18; }
        void SetSUnk18(const float sUnk18) { this->sUnk18 = sUnk18; }

    private:
        int sUnk00 = 0;
        int sUnk04 = 0;
        float sUnk08 = 0.0f;
        float sUnk0C = 0.0f;
        float sUnk14 = 0.0f;
        float sUnk18 = 0.0f;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;    };

    class GRIMHOOKER_API WeatherOverrideRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::WeatherOverride;

        explicit WeatherOverrideRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetWeatherLotId() const { return weatherLotId; }
        void SetWeatherLotId(const int weatherLotId) { this->weatherLotId = weatherLotId; }

    private:
        int weatherLotId = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };

    class GRIMHOOKER_API AutoDrawGroupPointRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::AutoDrawGroupPoint;

        explicit AutoDrawGroupPointRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetSUnk00() const { return sUnk00; }
        void SetSUnk00(const int sUnk00) { this->sUnk00 = sUnk00; }

    private:
        int sUnk00 = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };

    class GRIMHOOKER_API GroupDefeatRewardRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::GroupDefeatReward;

        explicit GroupDefeatRewardRegion(const std::string& name) : Region(name)
        {
            groupPartsIndices.fill(-1);
        }

        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetSUnk00() const { return sUnk00; }
        void SetSUnk00(const int sUnk00) { this->sUnk00 = sUnk00; }
        [[nodiscard]] int GetSUnk04() const { return sUnk04; }
        void SetSUnk04(const int sUnk04) { this->sUnk04 = sUnk04; }
        [[nodiscard]] int GetSUnk08() const { return sUnk08; }
        void SetSUnk08(const int sUnk08) { this->sUnk08 = sUnk08; }

        [[nodiscard]] Part* GetGroupPartAtIndex(const int index) const { return groupParts[index].Get(); }
        void SetGroupPartAtIndex(const int index, Part* const part) { groupParts[index].Set(part); }
        void SetGroupPartAtIndex(const int index, const std::unique_ptr<Part>& part) { groupParts[index].Set(part); }

        [[nodiscard]] int GetSUnk34() const { return sUnk34; }
        void SetSUnk34(const int sUnk34) { this->sUnk34 = sUnk34; }
        [[nodiscard]] int GetSUnk38() const { return sUnk38; }
        void SetSUnk38(const int sUnk38) { this->sUnk38 = sUnk38; }
        [[nodiscard]] int GetSUnk54() const { return sUnk54; }
        void SetSUnk54(const int sUnk54) { this->sUnk54 = sUnk54; }

        void DeserializeEntryReferences(const std::vector<Region*>& regions, const std::vector<Part*>& parts) override;
        void SerializeEntryIndices(const std::vector<Region*>& regions, const std::vector<Part*>& parts) override;

    private:
        int sUnk00 = 0;
        int sUnk04 = 0;
        int sUnk08 = 0;
        std::array<EntryReference<Part>, 8> groupParts{};
        std::array<int32_t, 8> groupPartsIndices{};  // TODO: always Characters (still by Part supertype index)?
        int sUnk34 = 0;
        int sUnk38 = 0;
        int sUnk54 = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };

    class GRIMHOOKER_API MapPointDiscoveryOverrideRegion final : public Region
    {
        // No data at all.
    public:
        static constexpr auto Type = RegionType::MapPointDiscoveryOverride;

        explicit MapPointDiscoveryOverrideRegion(const std::string& name) : Region(name) {}

        [[nodiscard]] RegionType GetType() const override { return Type; }
    };

    class GRIMHOOKER_API MapPointParticipationOverrideRegion final : public Region
    {
        // No data at all.
    public:
        static constexpr auto Type = RegionType::MapPointParticipationOverride;

        explicit MapPointParticipationOverrideRegion(const std::string& name) : Region(name) {}
        
        [[nodiscard]] RegionType GetType() const override { return Type; }
    };
    
    class GRIMHOOKER_API HitsetRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::Hitset;

        explicit HitsetRegion(const std::string& name) : Region(name) {}
        
        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetSUnk00() const { return sUnk00; }
        void SetSUnk00(const int sUnk00) { this->sUnk00 = sUnk00; }

    private:
        int sUnk00 = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;};
    
    class GRIMHOOKER_API FastTravelRestrictionRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::FastTravelRestriction;

        explicit FastTravelRestrictionRegion(const std::string& name) : Region(name) {}
        
        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] uint32_t GetEventFlagId() const { return eventFlagId; }
        void SetEventFlagId(const uint32_t eventFlagId) { this->eventFlagId = eventFlagId; }

    private:
        uint32_t eventFlagId = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };
    
    class GRIMHOOKER_API WeatherCreateAssetPointRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::WeatherCreateAssetPoint;

        explicit WeatherCreateAssetPointRegion(const std::string& name) : Region(name) {}
        
        [[nodiscard]] RegionType GetType() const override { return Type; }
    private:
        // No real data.
        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };
    
    class GRIMHOOKER_API PlayAreaRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::PlayArea;

        explicit PlayAreaRegion(const std::string& name) : Region(name) {}
        
        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetSUnk00() const { return sUnk00; }
        void SetSUnk00(const int sUnk00) { this->sUnk00 = sUnk00; }
        [[nodiscard]] int GetSUnk04() const { return sUnk04; }
        void SetSUnk04(const int sUnk04) { this->sUnk04 = sUnk04; }

    private:
        int sUnk00 = 0;
        int sUnk04 = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };
    
    class GRIMHOOKER_API EnvironmentMapOutputRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::EnvironmentMapOutput;

        explicit EnvironmentMapOutputRegion(const std::string& name) : Region(name) {}
        
        [[nodiscard]] RegionType GetType() const override { return Type; }

        // No subtype data at all (not even pads).
    };
    
    class GRIMHOOKER_API MountJumpRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::MountJump;

        explicit MountJumpRegion(const std::string& name) : Region(name) {}
        
        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] float GetJumpHeight() const { return jumpHeight; }
        void SetJumpHeight(const float jumpHeight) { this->jumpHeight = jumpHeight; }
        [[nodiscard]] int GetSUnk04() const { return sUnk04; }
        void SetSUnk04(const int sUnk04) { this->sUnk04 = sUnk04; }

    private:
        float jumpHeight = 0.0f;
        int sUnk04 = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };
    
    class GRIMHOOKER_API DummyRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::Dummy;

        explicit DummyRegion(const std::string& name) : Region(name) {}
        
        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetSUnk00() const { return sUnk00; }
        void SetSUnk00(const int sUnk00) { this->sUnk00 = sUnk00; }

    private:
        int sUnk00 = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };
    
    class GRIMHOOKER_API FallPreventionRemovalRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::FallPreventionRemoval;

        explicit FallPreventionRemovalRegion(const std::string& name) : Region(name) {}
        
        [[nodiscard]] RegionType GetType() const override { return Type; }
    private:
        // No real data, just pads.
        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };
    
    class GRIMHOOKER_API NavmeshCuttingRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::NavmeshCutting;

        explicit NavmeshCuttingRegion(const std::string& name) : Region(name) {}
        
        [[nodiscard]] RegionType GetType() const override { return Type; }
    private:
        // No real data, just pads.
        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };
    
    class GRIMHOOKER_API MapNameOverrideRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::MapNameOverride;

        explicit MapNameOverrideRegion(const std::string& name) : Region(name) {}
        
        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] int GetMapNameId() const { return mapNameId; }
        void SetMapNameId(const int mapNameId) { this->mapNameId = mapNameId; }

    private:
        int mapNameId = 0;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };
    
    class GRIMHOOKER_API MountJumpFallRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::MountJumpFall;

        explicit MountJumpFallRegion(const std::string& name) : Region(name) {}
        
        [[nodiscard]] RegionType GetType() const override { return Type; }

    private:
        // No real data, just pads.
        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };
    
    class GRIMHOOKER_API HorseRideOverrideRegion final : public Region
    {
    public:

        /// @brief Exhaustive values for `HorseRideOverrideRegion.overrideType`.
        enum class HorseRideOverrideType : int
        {
            Default = 0,
            Prevent = 1,
            Allow = 2
        };

        static constexpr auto Type = RegionType::HorseRideOverride;

        explicit HorseRideOverrideRegion(const std::string& name) : Region(name) {}
        
        [[nodiscard]] RegionType GetType() const override { return Type; }

        [[nodiscard]] HorseRideOverrideType GetOverrideType() const { return overrideType; }
        void SetOverrideType(const HorseRideOverrideType overrideType) { this->overrideType = overrideType; }

    private:
        HorseRideOverrideType overrideType = HorseRideOverrideType::Default;

        bool DeserializeSubtypeData(std::ifstream& stream) override;
        bool SerializeSubtypeData(std::ofstream& stream) const override;
    };
    
    class GRIMHOOKER_API OtherRegion final : public Region
    {
    public:
        static constexpr auto Type = RegionType::Other;

        explicit OtherRegion(const std::string& name) : Region(name) {}
        
        [[nodiscard]] RegionType GetType() const override { return Type; }

        // No subtype data at all (not even pads).
    };

    using RegionVariantType = std::variant<
        std::vector<std::unique_ptr<InvasionPointRegion>>,
        std::vector<std::unique_ptr<EnvironmentMapPointRegion>>,
        std::vector<std::unique_ptr<SoundRegion>>,
        std::vector<std::unique_ptr<VFXRegion>>,
        std::vector<std::unique_ptr<WindVFXRegion>>,
        std::vector<std::unique_ptr<SpawnPointRegion>>,
        std::vector<std::unique_ptr<MessageRegion>>,
        std::vector<std::unique_ptr<EnvironmentMapEffectBoxRegion>>,
        std::vector<std::unique_ptr<WindAreaRegion>>,
        std::vector<std::unique_ptr<ConnectionRegion>>,
        std::vector<std::unique_ptr<PatrolRoute22Region>>,
        std::vector<std::unique_ptr<BuddySummonPointRegion>>,
        std::vector<std::unique_ptr<MufflingBoxRegion>>,
        std::vector<std::unique_ptr<MufflingPortalRegion>>,
        std::vector<std::unique_ptr<OtherSoundRegion>>,
        std::vector<std::unique_ptr<MufflingPlaneRegion>>,
        std::vector<std::unique_ptr<PatrolRouteRegion>>,
        std::vector<std::unique_ptr<MapPointRegion>>,
        std::vector<std::unique_ptr<WeatherOverrideRegion>>,
        std::vector<std::unique_ptr<AutoDrawGroupPointRegion>>,
        std::vector<std::unique_ptr<GroupDefeatRewardRegion>>,
        std::vector<std::unique_ptr<MapPointDiscoveryOverrideRegion>>,
        std::vector<std::unique_ptr<MapPointParticipationOverrideRegion>>,
        std::vector<std::unique_ptr<HitsetRegion>>,
        std::vector<std::unique_ptr<FastTravelRestrictionRegion>>,
        std::vector<std::unique_ptr<WeatherCreateAssetPointRegion>>,
        std::vector<std::unique_ptr<PlayAreaRegion>>,
        std::vector<std::unique_ptr<EnvironmentMapOutputRegion>>,
        std::vector<std::unique_ptr<MountJumpRegion>>,
        std::vector<std::unique_ptr<DummyRegion>>,
        std::vector<std::unique_ptr<FallPreventionRemovalRegion>>,
        std::vector<std::unique_ptr<NavmeshCuttingRegion>>,
        std::vector<std::unique_ptr<MapNameOverrideRegion>>,
        std::vector<std::unique_ptr<MountJumpFallRegion>>,
        std::vector<std::unique_ptr<HorseRideOverrideRegion>>,
        std::vector<std::unique_ptr<OtherRegion>>
    >;
}
