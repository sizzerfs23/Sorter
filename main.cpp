#include <iostream>
#include <cstring>
#include <filesystem>
#include <vector>



int main(int argc, char* argv[]) {
    bool succel = false;
    if(argc >= 3) {
        if(!strcmp(argv[1], "sort")) {

            //based

            std::vector<std::pair<std::string, std::string>> extensions = {
                {".jpg", "image"},
                {".png", "image"},
                {".mp4", "video"},
                {".txt", "textet"},
                {".mp3", "music"},
                {".pdf", "doc"},
                {".sh" , "binares"},
                {".zip", "archives"},
                {".deb", "archives"},
                {".torrent", "torrents"}   
            };

            //logic 

            for(const auto& entry : std::filesystem::directory_iterator(argv[2])) {
                auto p = entry.path();
                if(entry.is_regular_file()) {
                    
                    auto rash = p.extension();
                    auto parent = p.parent_path();
                    
                    for(int i = 0; i < extensions.size(); i++) {
                            if(extensions[i].first == rash) {
                                succel = true;
                                std::cout << "\n\n------------------------------------" << "\n";
                                std::cout << p.filename() << " <- " << extensions[i].second << " type " << "\n";
                                std::cout << " ↓ " << "\n";
                                std::cout << parent / extensions[i].second << "\n" ;
                                std::cout << "------------------------------------" << "\n\n";
                                if(!(std::filesystem::is_directory(parent / extensions[i].second))) {
                                std::filesystem::create_directory(parent / extensions[i].second);
                                } 
                                std::filesystem::rename(p, parent / extensions[i].second / p.filename()) ;
                                break;
                            }
                        }        
                }else {
                    
                    continue;
                }         
                
            }
            if(!succel) {
                std::cout << "\n------------------------------------\n";
                std::cout << "Подходящих решений не было найдено!";
                std::cout << "\n------------------------------------\n";
            }
        } else {
            return 1;
        }
    } else {
        return 1;
    }
}