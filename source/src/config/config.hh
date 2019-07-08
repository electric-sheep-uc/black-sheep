#pragma once

#include <map>

#include "json.hh"

/**
 * config.hh
 *
 * Allow the program configuration to be interacted with.
 **/
class Config{
  private:
    std::vector<std::string> files;
    std::vector<time_t> lastMods;
    const char* temp;
    nlohmann::json jTemp;
    nlohmann::json jData;
    nlohmann::json jDelta;
    std::map<std::string, std::shared_ptr<int>> iVals;
    std::map<std::string, std::shared_ptr<long long>> lVals;
    std::map<std::string, std::shared_ptr<double>> dVals;

    /**
     * loadTemplate()
     *
     * Loads the default values from the template into the data JSON store.
     *
     * @param j The JSON data pre-loaded with the template.
     * @return The correct data pattern.
     **/
    nlohmann::json loadTemplate(nlohmann::json j);

    /**
     * getObject()
     *
     * Get a JSON object.
     *
     * @param name The path to the desired object.
     * @param j The JSON object to find a value from a path on.
     * @return The JSON object.
     **/
    nlohmann::json getObject(std::string name, nlohmann::json j);

    /**
     * mergeObject()
     *
     * Create a JSON object ready for merging from a name patch.
     *
     * @param name The path to the desired object.
     * @param value The value to set at the desired path.
     * @return The JSON merge object.
     **/
    nlohmann::json mergeObject(std::string name, std::string value);

    /**
     * service()
     *
     * Load in all external sources of configuration data in the correct order.
     *
     * @return True if a service was performed, otherwise false. This may be
     * because the configuration file was unable to be read.
     **/
    bool service();

    /**
     * checkValues()
     *
     * Check the values of input data verses the specified template.
     *
     * @param jD The JSON data.
     * @param jT The JSONS template.
     * @return True if the data is correct to the template, false otherwise.
     **/
    bool checkValues(nlohmann::json jD, nlohmann::json jT);

  public:
    /**
     * Config()
     *
     * Creation of a blank configuration data structure.
     **/
    Config();

    /**
     * Config()
     *
     * Open a configuration file from disk.
     *
     * @param filename The file to be loaded from disk.
     * @param isTemplate True if template configuration only, otherwise false.
     **/
    Config(const char* filename, bool isTemplate);

    /**
     * ~Config()
     *
     * Handle the closing of the configuration file.
     **/
    ~Config();

    /**
     * watchFile()
     *
     * Watch a configuration file for changes (requires pulling of the update()
     * function).
     *
     * @param filename The filename of the configuration file.
     * @return True if file can be watched, otherwise false.
     **/
    bool watchFile(const char* filename);

    /**
     * update()
     *
     * Update our idea of the state of various externally controlled
     * configuration sources. If changes are detected, we need to service all
     * of them using the service() function. This ensures changes are layered
     * correctly with overriding rules
     **/
    void update();

    /**
     * setObject()
     *
     * Set an object in the configuration file.
     *
     * @param name The name of the configuration to be set.
     * @param The value to be set.
     **/
    void setObject(std::string name, std::string value);

    /**
     * getString()
     *
     * Get a string from the configuration file.
     *
     * @param name The name of the configuration to be loaded.
     * @returm The requested string value.
     **/
    std::string getString(std::string name);

    /**
     * getInt()
     *
     * Get an integer from the configuration file.
     *
     * @param name The name of the configuration to be loaded.
     * @returm The requested int value.
     **/
    std::shared_ptr<int> getInt(std::string name);

    /**
     * getLong()
     *
     * Get an long long from the configuration file. For safety the value is
     * long long, if you already need a very large value, you may as well be on
     * the safe side.
     *
     * @param name The name of the configuration to be loaded.
     * @returm The requested long value.
     **/
    std::shared_ptr<long long> getLong(std::string name);

    /**
     * getDouble()
     *
     * Get an double from the configuration file.
     *
     * @param name The name of the configuration to be loaded.
     * @returm The requested double value.
     **/
    std::shared_ptr<double> getDouble(std::string name);

    /**
     * getLength()
     *
     * Get the length of an array.
     *
     * @param name The path to an array.
     * @return The length of the array.
     **/
    int getLength(std::string name);

    /**
     * getDump()
     *
     * Get a dump of the JSON file.
     *
     * @return A snapshot of the current JSON file status.
     **/
    std::string getDump();

    /**
     * getTemplateDump()
     *
     * Get a template dump of the JSON configuration.
     *
     * @return A snapshot of the current JSON template.
     **/
    std::string getTempDump();

    /**
     * write()
     *
     * Write the current delta configuration to disk.
     **/
    void write();
};
