"""CS 61A Presents The Game of Hog."""

from dice import six_sided, four_sided, make_test_dice
from ucb import main, trace, interact

GOAL_SCORE = 100  # The goal of Hog is to score 100 points.

######################
# Phase 1: Simulator #
######################


def roll_dice(num_rolls, dice=six_sided):
    """Simulate rolling the DICE exactly NUM_ROLLS > 0 times. Return the sum of
    the outcomes unless any of the outcomes is 1. In that case, return 1.

    num_rolls:  The number of dice rolls that will be made.
    dice:       A function that simulates a single dice roll outcome.

    >>> fixed_dice = make_test_dice(3, 4, 1)
    >>> roll_dice(2, dice=fixed_dice)
    7
    >>> roll_dice(2, dice=fixed_dice)
    1
    >>> roll_dice(2, dice=fixed_dice)
    1
    """
    # These assert statements ensure that num_rolls is a positive integer.
    assert type(num_rolls) == int, 'num_rolls must be an integer.'
    assert num_rolls > 0, 'Must roll at least once.'
    # BEGIN PROBLEM 1
    "*** YOUR CODE HERE ***"
    total_points = 0
    flag_one = 0
    for i in range(0, num_rolls):
        point = dice()
        # print(i, ":", point)
        total_points += point
        if point == 1:
            flag_one = 1

    if flag_one:
        return 1
    else:
        return total_points
    # END PROBLEM 1


def free_bacon(score):
    """Return the points scored from rolling 0 dice (Free Bacon).

    score:  The opponent's current score.

    >>> free_bacon(4)
    3
    >>> free_bacon(1)
    2
    >>> free_bacon(20)
    9
    >>> free_bacon(45)
    13
    """
    assert score < 100, 'The game should be over.'
    # BEGIN PROBLEM 2
    "*** YOUR CODE HERE ***"
    free_bacon_score = 0
    cube_score = score ** 3
    sign = 0
    while cube_score > 0:
        # free_bacon_score += ((-1) ** sign) * (cube_score % 10)
        if sign % 2:
            free_bacon_score -= cube_score % 10
        else:
            free_bacon_score += cube_score % 10
        cube_score //= 10
        sign += 1
    return 1 + abs(free_bacon_score)
    # END PROBLEM 2


def take_turn(num_rolls, opponent_score, dice=six_sided):
    """Simulate a turn rolling NUM_ROLLS dice, which may be 0 (Free Bacon).
    Return the points scored for the turn by the current player.

    num_rolls:       The number of dice rolls that will be made.
    opponent_score:  The total score of the opponent.
    dice:            A function that simulates a single dice roll outcome.
    
    >>> take_turn(2, 0, make_test_dice(4, 5, 1))
    9
    >>> take_turn(3, 0, make_test_dice(4, 6, 1))
    1
    >>> take_turn(0, 56)
    13
    >>> take_turn(0, 47)
    6
    """
    # Leave these assert statements here; they help check for errors.
    assert type(num_rolls) == int, 'num_rolls must be an integer.'
    assert num_rolls >= 0, 'Cannot roll a negative number of dice in take_turn.'
    assert num_rolls <= 10, 'Cannot roll more than 10 dice.'
    assert opponent_score < 100, 'The game should be over.'
    # BEGIN PROBLEM 3
    "*** YOUR CODE HERE ***"
    if num_rolls:
        return roll_dice(num_rolls, dice)
    else:
        return free_bacon(opponent_score)
    # END PROBLEM 3


def is_swap(player_score, opponent_score):
    """
    Return whether the two scores should be swapped
    
    >>> is_swap(2, 4)
    False
    >>> is_swap(11, 1)
    False
    >>> is_swap(1, 0)
    True
    >>> is_swap(23, 4)
    True
    """
    # BEGIN PROBLEM 4
    "*** YOUR CODE HERE ***"
    cube_scores = 3 ** (player_score + opponent_score)
    last = cube_scores % 10
    while cube_scores > 0:
        if cube_scores < 10 and cube_scores == last:
            return True
        cube_scores //= 10
    return False
    # END PROBLEM 4


def other(who):
    """Return the other player, for a player WHO numbered 0 or 1.

    >>> other(0)
    1
    >>> other(1)
    0
    """
    return 1 - who


def silence(score0, score1):
    """Announce nothing (see Phase 2)."""
    return silence


def play(strategy0, strategy1, score0=0, score1=0, dice=six_sided,
         goal=GOAL_SCORE, say=silence, feral_hogs=True):
    """Simulate a game and return the final scores of both players, with Player
    0's score first, and Player 1's score second.

    A strategy is a function that takes two total scores as arguments (the
    current player's score, and the opponent's score), and returns a number of
    dice that the current player will roll this turn.

    strategy0:  The strategy function for Player 0, who plays first.
    strategy1:  The strategy function for Player 1, who plays second.
    score0:     Starting score for Player 0
    score1:     Starting score for Player 1
    dice:       A function of zero arguments that simulates a dice roll.
    goal:       The game ends and someone wins when this score is reached.
    say:        The commentary function to call at the end of the first turn.
    feral_hogs: A boolean indicating whether the feral hogs rule should be active.

    >>> # We recommend working this out turn-by-turn on a piece of paper (use `python` for difficult calculations).
    >>> always_seven = make_test_dice(7)
    >>> strat0 = lambda score, opponent: opponent % 10
    >>> strat1 = lambda score, opponent: max((score // 10) - 4, 0)
    >>> s0, s1 = play(strat0, strat1, score0=71, score1=80, dice=always_seven, feral_hogs=False)
    >>> s0
    78
    >>> s1
    108
    >>> def strat0(s0, s1):
    ...     if s0 == 0: return 3
    ...     if s0 == 7: return 5
    ...     return 8
    >>> def strat1(s0, s1):
    ...     if s0 == 0: return 1
    ...     if s0 == 4: return 2
    ...     return 6
    >>> test_dice = make_test_dice(2, 2, 3, 4, 2, 2, 2, 2, 2, 3, 5, 2, 2, 2, 2, 2, 2, 2, 6, 1)
    >>> s0, s1 = play(strat0, strat1, score0=0, score1=0, goal=21, dice=test_dice) # Test problem 5b.
    >>> s0
    43
    >>> s1
    15
    """
    who = 0  # Who is about to take a turn, 0 (first) or 1 (second)
    # BEGIN PROBLEM 5
    "*** YOUR CODE HERE ***"
    last_score0, last_score1 = 0, 0
    while score0 < goal and score1 < goal:
        if who:     # player 1
            dice_num = strategy1(score1, score0)
            current_score = take_turn(dice_num, score0, dice)
            score1 += current_score
            if feral_hogs:
                if abs(dice_num - last_score1) == 2:
                    score1 += 3
                last_score1 = current_score
        else:
            dice_num = strategy0(score0, score1)
            current_score = take_turn(dice_num, score1, dice)
            score0 += current_score
            if feral_hogs:
                if abs(dice_num - last_score0) == 2:
                    score0 += 3
                last_score0 = current_score

        if is_swap(score0, score1):
            score0, score1 = score1, score0

        who = other(who)
        # END PROBLEM 5
        # (note that the indentation for the problem 6 prompt (***YOUR CODE HERE***) might be misleading)
        # BEGIN PROBLEM 6
        "*** YOUR CODE HERE ***"
        say = say(score0, score1)
        # END PROBLEM 6
    return score0, score1


#######################
# Phase 2: Commentary #
#######################


def say_scores(score0, score1):
    """A commentary function that announces the score for each player."""
    print("Player 0 now has", score0, "and Player 1 now has", score1)
    return say_scores


def announce_lead_changes(prev_leader=None):
    """Return a commentary function that announces lead changes.

    >>> f0 = announce_lead_changes()
    >>> f1 = f0(5, 0)
    Player 0 takes the lead by 5
    >>> f2 = f1(5, 12)
    Player 1 takes the lead by 7
    >>> f3 = f2(8, 12)
    >>> f4 = f3(8, 13)
    >>> f5 = f4(15, 13)
    Player 0 takes the lead by 2
    """
    def say(score0, score1):
        if score0 > score1:
            leader = 0
        elif score1 > score0:
            leader = 1
        else:
            leader = None
        if leader != None and leader != prev_leader:
            print('Player', leader, 'takes the lead by', abs(score0 - score1))
        return announce_lead_changes(leader)
    return say


def both(f, g):
    """Return a commentary function that says what f says, then what g says.

    NOTE: the following game is not possible under the rules, it's just
    an example for the sake of the doctest

    >>> h0 = both(say_scores, announce_lead_changes())
    >>> h1 = h0(10, 0)
    Player 0 now has 10 and Player 1 now has 0
    Player 0 takes the lead by 10
    >>> h2 = h1(10, 6)
    Player 0 now has 10 and Player 1 now has 6
    >>> h3 = h2(6, 17)
    Player 0 now has 6 and Player 1 now has 17
    Player 1 takes the lead by 11
    """
    def say(score0, score1):
        return both(f(score0, score1), g(score0, score1))
    return say


def announce_highest(who, prev_high=0, prev_score=0):
    """Return a commentary function that announces when WHO's score
    increases by more than ever before in the game.

    NOTE: the following game is not possible under the rules, it's just
    an example for the sake of the doctest

    >>> f0 = announce_highest(1) # Only announce Player 1 score gains
    >>> f1 = f0(12, 0)
    >>> f2 = f1(12, 11)
    11 point(s)! That's the biggest gain yet for Player 1
    >>> f3 = f2(20, 11)
    >>> f4 = f3(13, 20)
    >>> f5 = f4(20, 35)
    15 point(s)! That's the biggest gain yet for Player 1
    >>> f6 = f5(20, 47) # Player 1 gets 12 points; not enough for a new high
    >>> f7 = f6(21, 47)
    >>> f8 = f7(21, 77)
    30 point(s)! That's the biggest gain yet for Player 1
    >>> f9 = f8(77, 22) # Swap!
    >>> f10 = f9(33, 77) # Swap!
    55 point(s)! That's the biggest gain yet for Player 1
    """
    assert who == 0 or who == 1, 'The who argument should indicate a player.'
    # BEGIN PROBLEM 7
    "*** YOUR CODE HERE ***"
    def count_highest(score0, score1, p_high=prev_high, p_score=prev_score):
        if who:     # player 1
            gain = score1 - p_score
            p_score = score1
        else:       # player 0
            gain = score0 - p_score
            p_score = score0

        if gain > p_high:
            print(gain, "point(s)! That's the biggest gain yet for Player", who)
            p_high = gain
        # print(score0, score1, prev_high, prev_score)
        return announce_highest(who, p_high, p_score)
    return count_highest
    # END PROBLEM 7


#######################
# Phase 3: Strategies #
#######################


def always_roll(n):
    """Return a strategy that always rolls N dice.

    A strategy is a function that takes two total scores as arguments (the
    current player's score, and the opponent's score), and returns a number of
    dice that the current player will roll this turn.

    >>> strategy = always_roll(5)
    >>> strategy(0, 0)
    5
    >>> strategy(99, 99)
    5
    """
    def strategy(score, opponent_score):
        return n
    return strategy


def make_averaged(g, num_samples=1000):
    """Return a function that returns the average value of G when called.

    To implement this function, you will have to use *args syntax, a new Python
    feature introduced in this project.  See the project description.

    >>> dice = make_test_dice(4, 2, 5, 1)
    >>> averaged_dice = make_averaged(dice, 1000)
    >>> averaged_dice()
    3.0
    """
    # BEGIN PROBLEM 8
    "*** YOUR CODE HERE ***"
    def do_avg(*args):
        count = 0
        for i in range(0, num_samples):
            count += g(*args)
        return count/num_samples
    return do_avg
   # END PROBLEM 8


def max_scoring_num_rolls(dice=six_sided, num_samples=1000):
    """Return the number of dice (1 to 10) that gives the highest average turn
    score by calling roll_dice with the provided DICE over NUM_SAMPLES times.
    Assume that the dice always return positive outcomes.

    >>> dice = make_test_dice(1, 6)
    >>> max_scoring_num_rolls(dice)
    1
    """
    # BEGIN PROBLEM 9
    "*** YOUR CODE HERE ***"
    max_scoring, max_scoring_num = 0, 0
    for i in range(1, 11):
        avg = make_averaged(roll_dice, num_samples)(i, dice)
        if avg > max_scoring:
            max_scoring = avg
            max_scoring_num = i
    return max_scoring_num
    # END PROBLEM 9


def winner(strategy0, strategy1):
    """Return 0 if strategy0 wins against strategy1, and 1 otherwise."""
    score0, score1 = play(strategy0, strategy1)
    if score0 > score1:
        return 0
    else:
        return 1


def average_win_rate(strategy, baseline=always_roll(6)):
    """Return the average win rate of STRATEGY against BASELINE. Averages the
    winrate when starting the game as player 0 and as player 1.
    """
    win_rate_as_player_0 = 1 - make_averaged(winner)(strategy, baseline)
    win_rate_as_player_1 = make_averaged(winner)(baseline, strategy)

    return (win_rate_as_player_0 + win_rate_as_player_1) / 2


def run_experiments():
    """Run a series of strategy experiments and report results."""
    if True:  # Change to False when done finding max_scoring_num_rolls
        six_sided_max = max_scoring_num_rolls(six_sided)
        print('Max scoring num rolls for six-sided dice:', six_sided_max)

    if False:  # Change to True to test always_roll(8)
        print('always_roll(8) win rate:', average_win_rate(always_roll(8)))

    if False:  # Change to True to test bacon_strategy
        print('bacon_strategy win rate:', average_win_rate(bacon_strategy))

    if False:  # Change to True to test swap_strategy
        print('swap_strategy win rate:', average_win_rate(swap_strategy))

    if False:  # Change to True to test final_strategy
        print('final_strategy win rate:', average_win_rate(final_strategy))

    "*** You may add additional experiments as you wish ***"



def bacon_strategy(score, opponent_score, margin=8, num_rolls=6):
    """This strategy rolls 0 dice if that gives at least MARGIN points, and
    rolls NUM_ROLLS otherwise.

    >>> bacon_strategy(0, 9, margin=8, num_rolls=5)
    0
    >>> bacon_strategy(9, 0, margin=6, num_rolls=5)
    5
    """
    # BEGIN PROBLEM 10
    free_bacon_score = free_bacon(opponent_score)
    if free_bacon_score >= margin:
        return 0
    return num_rolls
    # END PROBLEM 10


def swap_strategy(score, opponent_score, margin=8, num_rolls=6):
    """This strategy rolls 0 dice when it triggers a beneficial swap. It also
    rolls 0 dice if it gives at least MARGIN points and does not trigger a
    non-beneficial swap. Otherwise, it rolls NUM_ROLLS.

    >>> swap_strategy(1, 19, 8, 6)
    0
    >>> swap_strategy(24, 1, 1, 6)
    6
    >>> swap_strategy(13, 18, 1, 6)
    0
    >>> swap_strategy(30, 54, 7, 6)
    6
    """
    # BEGIN PROBLEM 11
    swap_score = score + free_bacon(opponent_score)
    if is_swap(swap_score, opponent_score) and swap_score < opponent_score:
        # print("step 1 return")
        return 0
    if bacon_strategy(score, opponent_score, margin, num_rolls) == 0:
        after_free_bacon = score + free_bacon(opponent_score)
        # print(after_free_bacon, opponent_score)
        if is_swap(after_free_bacon, opponent_score) and after_free_bacon > opponent_score:
            return num_rolls
        else:
            # print("step 2 return")
            return 0
    return num_rolls
    # END PROBLEM 11


def final_strategy(score, opponent_score):
    """Write a brief description of your final strategy.

    *** YOUR DESCRIPTION HERE ***
    """
    # BEGIN PROBLEM 12
    return 6  # Replace this statement
    # END PROBLEM 12

##########################
# Command Line Interface #
##########################

# NOTE: Functions in this section do not need to be changed. They use features
# of Python not yet covered in the course.


@main
def run(*args):
    """Read in the command-line argument and calls corresponding functions.

    This function uses Python syntax/techniques not yet covered in this course.
    """
    import argparse
    parser = argparse.ArgumentParser(description="Play Hog")
    parser.add_argument('--run_experiments', '-r', action='store_true',
                        help='Runs strategy experiments')

    args = parser.parse_args()

    if args.run_experiments:
        run_experiments()