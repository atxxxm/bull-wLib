#pragma once
#include <string>
#include <vector>

namespace bull
{
    const std::string init_dir = ".bull"; 
    const std::string base_branch = "base"; 
    const std::string data_list = "data_list.txt"; 
    const std::string bullgnore = ".bullgnore"; 
    const std::string branch_list = "HEAD"; 
    const std::string config = "CONFIG"; 
    const std::string commit_list = "commit_list"; 
    const std::string file_list = "file_list"; 
    const std::string lang_config = "LANG"; 

    bool isBinaryFile(const std::string& filename);

    std::string current_branch(); 

    bool is_branch(const std::string& branch); 

    bool is_commit(const std::string& hash); 

    int getLineCommit(const std::string& hash, const std::string& commit_name); 

    std::string getLastCommit(); 

    std::string getCurrentLang(); 

    class _init_ 
    {
        private:
            std::vector<std::string> ignore_list; 
            void collect_ignore(); 
            void checkEdit(); 
            bool isInitDir();
        public:
            void init(); 
            void add(); 
            void ignore(); 
            void branch(const std::string& name); 
            void list_branch(); 
            void status(); 
            void changeLang(const std::string& lang); 
    };

    class _action_ 
    {
        private:
            std::string hash_gen(); 
            bool isMoreOne();
            bool isInitDir();
            std::string select_random_branch(const std::string& exclude);
            void show_func(const std::string& commit_hash);
            void comm_list_func(const std::string& commit_hash);

            void archive_func(const std::string& commit_hash, const std::string& name);
        public:
            void pack(const std::string& commit); 
            void unpack(const std::string& hash); 
            void set(const std::string& branch_name); 
            void remove_branch(const std::string& branch_name); 
            void remove_commit(const std::string& commit_hash); 
            void log(); 
            void reset(); 
            void show(const std::string& commit_hash);
            void show_last();
            void show_cur(const std::string& filename);
            void comm_list(const std::string& commit_hash);
            void comm_list_last();
            void archive_last_commit(const std::string& name);
            void archive_current_commit(const std::string& commit_hash, const std::string& name);

            ~_action_() {}
    };
}
