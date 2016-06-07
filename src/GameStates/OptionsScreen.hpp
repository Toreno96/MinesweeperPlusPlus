#pragma once

#include <unordered_map>
#include "GameState.hpp"
#include "GameLogic/Options.hpp"
#include "Graphics/BackButton.hpp"
#include "Graphics/NextChoiceButton.hpp"
#include "Graphics/PreviousChoiceButton.hpp"
#include "Graphics/Title.hpp"

class OptionsScreen : public GameState {
  public:
    OptionsScreen( Game *game );

    void handleInput() override;
    void update() override;
    void draw() override;
  protected:
    void positionDrawables() override;
    
    void fillOptionsNames();
    void fillCurrentlyChosenOptions();
    void fillPreviousOptionButtons();
    void fillNextOptionButtons();
    
    std::function< void() > createPreviousCellsShapeFunction();
    std::function< void() > createPreviousDifficultyFunction();
    std::function< void() > createDecrementRowsFunction();
    std::function< void() > createDecrementColumnsFunction();
    std::function< void() > createDecrementMinesFunction();
    std::function< void() > createNextCellsShapeFunction();
    std::function< void() > createNextDifficultyFunction();
    std::function< void() > createIncrementRowsFunction();
    std::function< void() > createIncrementColumnsFunction();
    std::function< void() > createIncrementMinesFunction();
    
    void positionOptionName( const std::string &keyToOption, const std::string &keyToOtherOption );
    void positionPreviousOptionButton( const std::string &keyToOption, const std::string &keyToOtherOption );
    void positionCurrentlyChosenOption( const std::string &keyToOption );
    void positionNextOptionButton( const std::string &keyToOption );
    void positionOptionBelowTheOther( const std::string &keyToOption, const std::string &keyToOtherOption );
    
    void updateCurrentlyChosenCellsShape();
    void updateCurrentlyChosenDifficulty();
    void updateCurrentlyChosenDimensions();
    void updateCurrentlyChosenOptions();
    
    // Składowe:
    Title mTitle;
    BackButton mBackButton; 
    std::unordered_map< std::string, ExtendedText > mOptionsNames;
    std::unordered_map< std::string, ExtendedText > mCurrentlyChosenOptions;
    std::unordered_map< std::string, PreviousChoiceButton > mPreviousOptionButtons;
    std::unordered_map< std::string, NextChoiceButton > mNextOptionButtons;
};