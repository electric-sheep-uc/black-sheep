#include "mitecom-roledecider.h"

#include <tgmath.h>

/**
 * Decide which role this robot will be, depending on the number of team mates and their distance to the ball.
 *
 * WARNING: This is example code for demonstration purposes only. The code will handle up to 4 robots and will
 * assign one striker, two supporters and one defender. Implement your own code here.
 *
 * @param teamMates, collection of all other team mates
 * @param my own ID
 * @return new role for this robot
 */
MixedTeamRoleEnum decideRole(const MixedTeamMates &teamMates, const int myID) {

	MixedTeamMate myself = teamMates.find(myID)->second;
	int32_t myBallX = myself.data.find(BALL_RELATIVE_X)->second;
	int32_t myBallY = myself.data.find(BALL_RELATIVE_Y)->second;
	//quadratic euklidian distance
	int32_t myDistanceToBall =  ((0 - myBallX) * (0 - myBallX)) + ((0 - myBallY) * (0 - myBallY)) ;

	bool closest = true;
	bool furthest = true;

	for (std::map<uint16_t, MixedTeamMate>::const_iterator it = teamMates.begin(); it != teamMates.end(); it++) {
		MixedTeamMate mate = it->second;
		int32_t mateBallX = mate.data.find(BALL_RELATIVE_X)->second;
		int32_t mateBallY = mate.data.find(BALL_RELATIVE_Y)->second;
		int32_t mateDistanceToBall =  ((0 - mateBallX) * (0 - mateBallX)) + ((0 - mateBallY) * (0 - mateBallY)) ;

		//compare distances to ball
		if (mateDistanceToBall < myDistanceToBall) {
			closest = false;
		} else if (mateDistanceToBall > myDistanceToBall) {
			furthest = false;
		}
	}

	//decide on role
	if (teamMates.empty() || closest ) {
		return ROLE_STRIKER;
	} else if (!teamMates.empty() && furthest ) {
		return ROLE_DEFENDER;
	} else {
		return ROLE_SUPPORTER;
	}
}


/*------------------------------------------------------------------------------------------------*/

