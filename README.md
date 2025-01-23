# **Tafl C++ - Vikings Chess**

**Created by Teodor Patov**

*Tafl* is an ancient board game played on a board and popular in Scandinavia and parts of Northern Europe. The game is a battle simulation where one side **"The Defenders"** defend their king and the other **"THe Attackers"** try to capture it.

---

## **Game Overview**

Tafl is a two-player strategy game played on a grid-based board. One side plays as the **Defender**, aiming to protect the **King**, while the other side plays as the **Attacker**, trying to capture the King.

### **Objective**
- **Defender**: The main goal of the Defender is to move the **King** to one of the board’s corners to escape and win the game.
- **Attacker**: The Attacker’s goal is to surround the **King** on all four sides, capturing it to win the game.

---

## **Features**

### **1. Customizable Board Sizes**
Choose board size by your preferences. Available sizes are:
- 9x9
- 11x11
- 13x13

### **2. Piece Types**
The game includes several types of pieces with unique roles and abilities:
- **Defenders**: A figures controlled by the Defender player. They aim to protect the King.
- **Attackers**: A figures controlled by the Attacker player. Their goal is to capture the King, surrounding him from all sides.
- **King**: A special figure controlled by the Defender. It must be protected or guided to one of the corners to win the game.

### **3. Command List**
Players can interact with the game through a set of predefined commands:
- `1. Start a game`: Starts the game and print the choosen board
- `2. Quit the game`: Exit the game.
- `3. Move a piece (move sourceX sourceY destinationX destinationY)`: Move a figure from a source coordinates to destination coordinates
- `4. Undo the last move (back)`: Revert the previous move, allowing players to try a alternative strategy.
- `5. Get help (help)`: Display a help section outlining commands.
- `6. Display game information (info)`: Show additional game information such as captured figures

### **4. Game Logic**
The game logic encompasses the following key elements:
- **Figure Movement**: Each type of figures (Defender, Attacker, and King) has movement rules. Figures move along the board’s grid, like a rook in chess.
  
- **Capture Logic**: Logic for capturing regular figure and the King that should be surrounded by attackers from all sides to be captured.
  
- **King’s Escape**: The King can escape by moving to one of the corner squares. To win, the Defender must get the King to a corner square, while the Attacker must prevent this by surrounding the King.

- **Alternating Turns**: The game alternates between the Attacker and Defender players, each making moves in their turn.

---

## **Players Interaction**
Players can make a set of commands (move, help, info, back, quit) 

The game needs to be played by two players: 
- The **Attacker** tries to surround the **King** and prevent its escape.
- The **Defender** tries to keep the **King** safe, either by blocking the Attackers or guiding the King to one of the corners of the board.

---

## **Win Conditions**

- **Attacker Wins**: The Attacker wins by completely surrounding the King on all four sides.
- **Defender Wins**: The Defender wins if they manage to move the King to one of the corner squares on the board.
---

## **Game Flow**

1. **Start the Game**: Players choose board size. The game begins with the Attacker moving first.
2. **Making Turns**: Players take turns moving their figures and can make a back move.
3. **Endgame**: The game concludes when either the King escapes to a corner (Defender wins) or is captured (Attacker wins).
