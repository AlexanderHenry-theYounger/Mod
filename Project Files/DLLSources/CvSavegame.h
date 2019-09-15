#ifndef SAVEGAME_H
#define SAVEGAME_H

class FDataStreamBase;
enum SavegameVariableTypes;

#include "JustInTimeArray.h"
#include "BoolArray.h"

// enum values for each class used in the savegame.
// ideally each class using SavegameVariableTypes should have an index here.
// Extending to the end is savegame safe. Altering the existing layout isn't.
enum SavegameClassTypes
{
	SAVEGAME_CLASS_AREA,
	SAVEGAME_CLASS_MAP,
	SAVEGAME_CLASS_PLOT,
	SAVEGAME_CLASS_UNIT,
	SAVEGAME_CLASS_UNIT_AI,

	NUM_SAVEGAME_CLASS_TYPES,

	FIRST_SAVEGAME_CLASS_TYPES = 0,
};

class CvSavegameReaderBase;
class CvSavegameWriterBase;

class CvSavegameReader
{
public:
	CvSavegameReader(CvSavegameReaderBase& readerBase);
	CvSavegameReader(const CvSavegameReader& reader);

	void AssignClassType(SavegameClassTypes eType);

	void Read(SavegameVariableTypes& variable);

	void Read(int& variable);
	void Read(short& variable);
	void Read(char& variable);

	void Read(unsigned int& variable);
	void Read(unsigned short& variable);
	void Read(byte& variable);

	void Read(bool& variable);
	
	void Read(CvString& szString);
	void Read(CvWString& szString);
	
	template<class T>
	void Read(JustInTimeArray<T>& jitArray);

	void Read(BoolArray& baArray);
	void Read(PlayerBoolArray& array); 
	void Read(IDInfo& idInfo);

	template<typename T>
	void ReadEnum(T& variable);

	// workaround because we can't use references on bitfields
	template<typename T>
	T ReadBitfield(T variable);

	// Add all enums used in savegames
	void Read(CardinalDirectionTypes& variable) { Read((int&)variable); }
	void Read(CalendarTypes         & variable) { Read((int&)variable); }
	void Read(CustomMapOptionTypes  & variable) { Read((int&)variable); }
	void Read(DirectionTypes        & variable) { Read((int&)variable); }
	void Read(GameType              & variable) { Read((int&)variable); }
	void Read(PlayerTypes           & variable) { Read((int&)variable); }
	void Read(PlotTypes             & variable) { Read((int&)variable); }
	void Read(SlotClaim             & variable) { Read((int&)variable); }
	void Read(SlotStatus            & variable) { Read((int&)variable); }
	void Read(TeamTypes             & variable) { Read((int&)variable); }
	void Read(TurnTimerTypes        & variable) { Read((int&)variable); }
	
	// everything linked to xml file enums
	void Read(ArtStyleTypes         & variable) { ReadEnum(variable); }
	void Read(BonusTypes            & variable) { ReadEnum(variable); }
	void Read(BuildTypes            & variable) { ReadEnum(variable); }
	void Read(BuildingTypes         & variable) { ReadEnum(variable); }
	void Read(BuildingClassTypes    & variable) { ReadEnum(variable); }
	void Read(SpecialBuildingTypes  & variable) { ReadEnum(variable); }
	void Read(CivEffectTypes        & variable) { ReadEnum(variable); }
	void Read(CivicTypes            & variable) { ReadEnum(variable); }
	void Read(CivicOptionTypes      & variable) { ReadEnum(variable); }
	void Read(CivilizationTypes     & variable) { ReadEnum(variable); }
	void Read(ClimateTypes          & variable) { ReadEnum(variable); }
	void Read(ColorTypes            & variable) { ReadEnum(variable); }
	void Read(CultureLevelTypes     & variable) { ReadEnum(variable); }
	void Read(DiplomacyTypes        & variable) { ReadEnum(variable); }
	void Read(EmphasizeTypes        & variable) { ReadEnum(variable); }
	void Read(EraTypes              & variable) { ReadEnum(variable); }
	void Read(EuropeTypes           & variable) { ReadEnum(variable); }
	void Read(EventTypes            & variable) { ReadEnum(variable); }
	void Read(EventTriggerTypes     & variable) { ReadEnum(variable); }
	void Read(FatherTypes           & variable) { ReadEnum(variable); }
	void Read(FatherPointTypes      & variable) { ReadEnum(variable); }
	void Read(FeatureTypes          & variable) { ReadEnum(variable); }
	void Read(GameOptionTypes       & variable) { ReadEnum(variable); }
	void Read(GameSpeedTypes        & variable) { ReadEnum(variable); }
	void Read(GoodyTypes            & variable) { ReadEnum(variable); }
	void Read(HandicapTypes         & variable) { ReadEnum(variable); }
	void Read(HurryTypes            & variable) { ReadEnum(variable); }
	void Read(ImprovementTypes      & variable) { ReadEnum(variable); }
	void Read(LeaderHeadTypes       & variable) { ReadEnum(variable); }
	void Read(MemoryTypes           & variable) { ReadEnum(variable); }
	void Read(PlayerColorTypes      & variable) { ReadEnum(variable); }
	void Read(PlayerOptionTypes     & variable) { ReadEnum(variable); }
	void Read(ProfessionTypes       & variable) { ReadEnum(variable); }
	void Read(PromotionTypes        & variable) { ReadEnum(variable); }
	void Read(RouteTypes            & variable) { ReadEnum(variable); }
	void Read(SeaLevelTypes         & variable) { ReadEnum(variable); }
	void Read(TerrainTypes          & variable) { ReadEnum(variable); }
	void Read(TraitTypes            & variable) { ReadEnum(variable); }
	void Read(UnitTypes             & variable) { ReadEnum(variable); }
	void Read(UnitAITypes           & variable) { ReadEnum(variable); }
	void Read(UnitClassTypes        & variable) { ReadEnum(variable); }
	void Read(UnitCombatTypes       & variable) { ReadEnum(variable); }
	void Read(SpecialUnitTypes      & variable) { ReadEnum(variable); }
	void Read(VictoryTypes          & variable) { ReadEnum(variable); }
	void Read(YieldTypes            & variable) { ReadEnum(variable); }
	void Read(WorldSizeTypes        & variable) { ReadEnum(variable); }

	void ReadConversionTable();

	int ConvertIndex(JITarrayTypes eType, int iIndex) const;

#ifndef MakefileCompilation
	// remove IntelliSense errors, which causes bogus red lines in the code
	// This isn't compiled and won't effect the game at runtime

	void Read(wchar& variable); // the makefile will use short instead, but IntelliSense fail to detect this
#endif

private:

	void Read(byte* var, unsigned int iSize);
	int ReadBytes(int iNumBytes);
	unsigned int ReadUnsignedBytes(int iNumBytes);

	SavegameClassTypes m_eClassType;

	CvSavegameReaderBase& m_ReaderBase;
};

class CvSavegameWriter
{
public:
	CvSavegameWriter(CvSavegameWriterBase& writerbase);
	CvSavegameWriter(const CvSavegameWriter& writer);

	void AssignClassType(SavegameClassTypes eType);

	template<enum T>
	void Write(T variable);

	void Write(int iVar);
	void Write(short iVar);
	void Write(char iVar);
	void Write(unsigned int iVar);
	void Write(unsigned short iVar);
	void Write(byte iVar);

	void Write(bool bVar);

	void Write(CvString& szString);
	void Write(CvWString& szString);

	void Write(BoolArray& baArray);
	
	template<class T>
	void Write(JustInTimeArray<T>& jitArray);

	void Write(SavegameVariableTypes eType);
	void Write(SavegameVariableTypes eType, CvString& szString);
	void Write(SavegameVariableTypes eType, CvWString& szString);
	void Write(SavegameVariableTypes eType, BoolArray& baArray);
	void Write(SavegameVariableTypes eType, PlayerBoolArray& array);
	void Write(SavegameVariableTypes eType, IDInfo& idInfo);

	template<class T>
	void Write(SavegameVariableTypes eType, T eVariable, T eDefault);

	template<class T>
	void Write(SavegameVariableTypes eType, JustInTimeArray<T>& jitArray);
	
	// enum conversion
	void GenerateTranslationTable();
	void WriteTranslationTable();

private:

	void Write(byte*var, unsigned int iSize);

	SavegameClassTypes m_eClassType;

	std::vector<byte>& m_vector;
};

//
// Inline functions to allow easy handling of templates
//

//
// Reader
//

template<typename T>
inline void CvSavegameReader::ReadEnum(T& variable)
{
	Read((byte*)&variable, sizeof(T));
	variable = (T)ConvertIndex(getJITarrayType(variable), variable);
}

template<typename T>
inline T CvSavegameReader::ReadBitfield(T variable)
{
	Read(variable);
	return variable;
}

template<class T>
inline void CvSavegameReader::Read(JustInTimeArray<T>& jitArray)
{
	jitArray.Read(this);
}



//
// Writer
//

template<enum T>
inline void CvSavegameWriter::Write(T variable)
{
	Write((byte*)&variable, sizeof(T));
}

template<class T>
inline void CvSavegameWriter::Write(JustInTimeArray<T>& jitArray)
{
	jitArray.Write(this);
}

template<class T>
inline void CvSavegameWriter::Write(SavegameVariableTypes eType, T eVariable, T eDefault)
{
	if (eVariable != eDefault)
	{
		Write(eType);
		Write(eVariable);
	}
}

template<class T>
inline void CvSavegameWriter::Write(SavegameVariableTypes eType, JustInTimeArray<T>& jitArray)
{
	if (jitArray.hasContent())
	{
		Write(eType);
		Write(jitArray);
	}
}


///
/// base classes
/// do not work with these directly. Make once instance when called from the exe and that's it.
/// Instantly make an instance of the reader/writer with a reference to the base class and then use the reader/writer instead.
///
/// The idea is that the reader/writer will make a new instance for each function call.
/// Since they don't actually contain data, but rather references to the data in the base class, it works like it's just one instance.
/// However since it's one instance for each function call, it will be possible to add variables, which are local to the function in question.
///
/// This allows the reader/writer to be aware of which class it's working on without losing this info by calling some other classes.
/// For instance CvMap knows it's CvMap. It calls CvPlot multiple times, which then knows it's CvPlot, but when it returns, it's back to CvMap without any extra code.
///

class CvSavegameReaderBase
{
	friend class CvSavegameReader;
public:
	CvSavegameReaderBase(FDataStreamBase* pStream);

	~CvSavegameReaderBase();

private:

	void Read(byte* var, unsigned int iSize);

	FDataStreamBase* m_pStream;
	byte* m_Memory;
	byte* m_MemoryAllocation;
	byte *m_MemoryEnd;
	unsigned int m_iSize;
};

class CvSavegameWriterBase
{
	friend class CvSavegameWriter;
public:
	CvSavegameWriterBase(FDataStreamBase* pStream);

	void WriteFile();

private:

	FDataStreamBase* m_pStream;
	std::vector<byte> m_vector;
};

#endif