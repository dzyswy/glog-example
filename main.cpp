#include <glog/logging.h>
#include <iomanip>
#include <unistd.h>

void MyPrefixFormatter(std::ostream& s, const google::LogMessage& m, void* /*data*/) {
    s << google::GetLogSeverityName(m.severity())[0]
    << std::setw(4) << 1900 + m.time().year()
    << std::setw(2) << 1 + m.time().month()
    << std::setw(2) << m.time().day()
    << ' '
    << std::setw(2) << m.time().hour() << ':'
    << std::setw(2) << m.time().min()  << ':'
    << std::setw(2) << m.time().sec() << "."
    << std::setw(6) << m.time().usec()
    << ' '
    << std::setfill(' ') << std::setw(5)
    << m.thread_id() << std::setfill('0')
    << ' '
    << m.basename() << ':' << m.line() << "]";
}

void YourFailureFunction() {
  // Reports something...
  exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) 
{
    google::InstallPrefixFormatter(&MyPrefixFormatter);
    //google::InstallFailureFunction(&YourFailureFunction);
    google::InstallFailureSignalHandler();
    google::InitGoogleLogging(argv[0]);
    
    //FLAGS_logtostderr = 1;        //GLOG_logtostderr=1 ./your_application
    FLAGS_stderrthreshold = 0;
    FLAGS_minloglevel = 0;
    FLAGS_v = 1;
    FLAGS_vmodule = "main=2";

    int num_cookies = 12;
    LOG(INFO) << "Found " << num_cookies << " cookies"; 
    LOG(WARNING) << "Found " << num_cookies << " cookies"; 
    LOG(ERROR) << "Found " << num_cookies << " cookies"; 
    //LOG(FATAL) << "Found " << num_cookies << " cookies"; 


    LOG_IF(INFO, num_cookies > 10) << "Got lots of cookies";

    for (int i = 0; i < 100; i++) {
        LOG_EVERY_N(INFO, 10) << "Got the " << google::COUNTER << "th cookie";
    }

    for (int i = 0; i < 100; i++) {
        LOG_FIRST_N(INFO, 20) << "Got the " << google::COUNTER << "th cookie";
    }

    for (int i = 0; i < 100; i++) { 
        LOG_EVERY_T(INFO, 0.01) << "Got a cookie";
        usleep(1000);
    }

    for (int i = 0; i < 10; i++) { 
        LOG_EVERY_T(INFO, 2.35) << "Got a cookie";
        usleep(500000);
    }

    VLOG(1) << "I’m printed when you run the program with --v=1 or higher";
    VLOG(2) << "I’m printed when you run the program with --v=2 or higher";

    CHECK_NE(1, 2) << ": The world must be ending!";
    CHECK_EQ(std::string("abc")[1], 'b');
    //CHECK_NOTNULL(some_ptr);

    return 0;
}

