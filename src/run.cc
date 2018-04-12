#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>

#include <flutter_desktop_embedding/flutter_embedder.h>

static bool isSPCRLF(char c)
{
    return c == ' ' || c == '\r' || c == '\n';
}

static bool loadFile(const char *name, bool binary, std::string *buf, bool stripWS = false)
{
    std::ifstream ifs(name, binary ? std::ifstream::binary : std::ifstream::in);
    if (!ifs.is_open())
        return false;
    *buf = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    if (stripWS && !buf->empty())
    {
        while (isSPCRLF(buf->back()))
            buf->pop_back();
    }
    return !ifs.bad();
}

static bool fillOpts(flutter_desktop_embedding::Opts& opts, std::string& entry)
{
    // -k=v
    if (entry.size() < 4 || '-' != entry[0] || '=' != entry[2])
    {
        std::cout << "Invalid option: " << entry << std::endl;
        return false;
    }
    
    size_t colon;
    bool ok = true;
    switch (entry[1])
    {
        case 'x':
            opts.x = atoi(entry.data() + 3);
            break;
        case 'y':
            opts.y = atoi(entry.data() + 3);
            break;
        case 'w':
            opts.w = atoi(entry.data() + 3);
            break;
        case 'h':
            opts.h = atoi(entry.data() + 3);
            break;
        case 't':
            opts.title.assign(entry.data() + 3, entry.size() - 3);
            break;
        case 'e':
            if (std::string::npos != (colon = entry.find(':')) && colon != 3)
            {
                entry[colon] = '\0';
                setenv(entry.data() + 3, entry.c_str() + colon + 1, 0);
            }
            else
            {
                setenv(entry.c_str() + 3, "1", 0);
            }
            break;
        default:
            std::cout << "Unknown option: " << entry << std::endl;
            ok = false;
    }
    
    return ok;
}

static bool fillOpts(flutter_desktop_embedding::Opts& opts, const char* argv[], int offset, int count)
{
    std::string entry;
    if (count == 0)
    {
        // no args
        if (!loadFile("target/run.txt", false, &entry, true))
            return true;
        
        std::stringstream ss(entry);
        std::string to;
        while (std::getline(ss, to, '\n'))
        {
            while (isSPCRLF(to.back()))
                to.pop_back();
            
            // support comments
            if (!to.empty() && '#' != to.front() && !fillOpts(opts, to))
                return false;
        }
        
        return true;
    }
    
    while (count-- > 0)
    {
        entry.assign(argv[offset++]);
        if (!fillOpts(opts, entry))
            return false;
    }
    
    return true;
}

int main(int argc, const char* argv[])
{
    flutter_desktop_embedding::Opts opts;
    if (!fillOpts(opts, argv, 1, argc - 1))
        return EXIT_FAILURE;
    
    if (!glfwInit())
        std::cout << "Couldn't init GLFW\n";
    
    // Arguments for the Flutter Engine.
    int arg_count = 2;
    // First argument is argv[0] since the engine is expecting real command line
    // args.
    const char *args_arr[] = {
        argv[0],
        "--dart-non-checked-mode",
        NULL,
    };
    auto window = flutter_desktop_embedding::CreateFlutterWindowInSnapshotMode(
        opts,
        "app/build/flutter_assets",
        "lib/flutter/bin/cache/artifacts/engine/linux-x64/icudtl.dat",
        arg_count, const_cast<char **>(args_arr));
    
    int ret = EXIT_FAILURE;
    if (window)
    {
        flutter_desktop_embedding::FlutterWindowLoop(window);
        ret = EXIT_SUCCESS;
    }
    
    glfwTerminate();
    return ret;
}
