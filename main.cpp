#include <glog/logging.h>

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]); 
    int num_cookies = 10;
    LOG(WARNING) << "Found " << num_cookies << " cookies"; 
    return 0;
}

