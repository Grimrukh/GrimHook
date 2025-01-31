﻿#pragma once

#include <map>
#include <string>

#include "GrimHookER/Export.h"
#include "Entry.h"
#include "Enums.h"


namespace GrimHookER::Maps::MapStudio
{

    // MSB Model supertype
    class GRIMHOOKER_API Model : public Entry
    {
    public:
        using EnumType = ModelType;

        static constexpr int SubtypeEnumOffset = 8;

        [[nodiscard]] static const std::map<ModelType, std::string>& GetTypeNames()
        {
            static const std::map<ModelType, std::string> data =
            {
                {ModelType::MapPiece, "MapPiece"},
                {ModelType::Character, "Character"},
                {ModelType::Player, "Player"},
                {ModelType::Collision, "Collision"},
                {ModelType::Asset, "Asset"},
            };
            return data;
        }

        explicit Model(const std::string& name) : Entry(name) {}

        /// @brief Returns `static constexpr ModelType` defined in each subclass.
        [[nodiscard]] virtual ModelType GetType() const = 0;

        void SetInstanceCount(const int count) { instanceCount = count; }

        void Deserialize(std::ifstream& stream) override;
        void Serialize(std::ofstream& stream, int supertypeIndex, int subtypeIndex) const override;

        explicit operator std::string() const
        {
            return GetTypeNames().at(GetType()) + " " + m_name;
        }

    protected:
        std::string sibPath;
        int instanceCount = 0;
        int hUnk1C = 0;
    };

    class GRIMHOOKER_API MapPieceModel final : public Model
    {
    public:
        static constexpr auto Type = ModelType::MapPiece;

        explicit MapPieceModel(const std::string& name) : Model(name) {}
        MapPieceModel() : Model("m999999") {}

        [[nodiscard]] ModelType GetType() const override { return Type; }
    };

    // Asset model name is split into three-digit prefix and three-digit suffix. The prefix corresponds to a 'category'
    // and has a subfolder in the game data.
    class GRIMHOOKER_API AssetModel final : public Model
    {
    public:
        static constexpr auto Type = ModelType::Asset;

        explicit AssetModel(const std::string& name) : Model(name) {}
        AssetModel() : Model("AEG999_999") {}

        [[nodiscard]] ModelType GetType() const override { return Type; }
    };

    class GRIMHOOKER_API CharacterModel final : public Model
    {
    public:
        static constexpr auto Type = ModelType::Character;

        explicit CharacterModel(const std::string& name) : Model(name) {}
        CharacterModel() : Model("c9999") {}

        [[nodiscard]] ModelType GetType() const override { return Type; }
    };

    // Used for 'c0000' (equipment-supporting 'Human' model) only.
    class GRIMHOOKER_API PlayerModel final : public Model
    {
    public:
        static constexpr auto Type = ModelType::Player;

        explicit PlayerModel(const std::string& name) : Model(name) {}
        PlayerModel() : Model("c0000") {}

        [[nodiscard]] ModelType GetType() const override { return Type; }
    };

    // Used for both Collision and Connect Collision parts (and the latter typically reference the matching former).
    class GRIMHOOKER_API CollisionModel final : public Model
    {
    public:
        static constexpr auto Type = ModelType::Collision;

        explicit CollisionModel(const std::string& name) : Model(name) {}
        CollisionModel() : Model("h999999") {}

        [[nodiscard]] ModelType GetType() const override { return Type; }
    };
}
