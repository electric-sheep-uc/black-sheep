#pragma once

#include "config/config.hh"
#include "localization/localization.hh"
#include "motion/motion.hh"
#include "network/gamestate.hh"
#include "network/teamstate.hh"
#include "utils/timing.hh"
#include "vision/vision.hh"

/**
 * main.hh
 *
 * Entry point into the program, responsible for taking command line arguments
 * and running the program appropriately.
 **/
class Main{
  public:
    static Config* config;
    static Localization* loc;
    static Motion* mot;
    static GameState* gs;
    static TeamState* ts;
    static Timing* time;
    static Vision* vis;

    /**
     * printWelcome()
     *
     * Display a welcome message with useful information to the person running
     * the program.
     **/
    static void printWelcome();

    /**
     * help()
     *
     * Display help for the accepted command line arguments.
     *
     * @param argv The command line arguments.
     * @param argc The number of arguments.
     * @param x The current offset into the parameters.
     * @return The new offset into the parameters.
     **/
    static int help(char** argv, int argc, int x);

    /**
     * motor()
     *
     * Allow motors to be directly controlled via the terminal.
     *
     * @param argv The command line arguments.
     * @param argc The number of arguments.
     * @param x The current offset into the parameters.
     * @return The new offset into the parameters.
     **/
    static int motor(char** argv, int argc, int x);

    /**
     * mainThread()
     *
     * Run the main thread.
     **/
    static void mainThread();

    /**
     * visThread()
     *
     * Run the vision thread.
     **/
    static void visThread();

    /**
     * hwThread()
     *
     * Rum the hardware thread.
     **/
    static void hwThread();

    /**
     * wwwThread()
     *
     * Rum the server thread.
     **/
    static void wwwThread();

    /**
     * gameThread()
     *
     * Run the game state thread.
     **/
    static void gameThread();

    /**
     * teamThread()
     *
     * Run the team state thread.
     **/
    static void teamThread();
};
