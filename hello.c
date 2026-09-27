#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(void) {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in a;
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    a.sin_addr.s_addr = INADDR_ANY;
    a.sin_port = htons(8080);
    bind(s, (struct sockaddr *)&a, sizeof(a));
    listen(s, 8);
    const char *resp =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<h1>Hello World</h1>\n";
    char buf[1024];
    for (;;) {
        int c = accept(s, 0, 0);
        if (c < 0) continue;
        read(c, buf, sizeof(buf));      /* read the request, ignore it */
        write(c, resp, strlen(resp));   /* send the fixed page */
        close(c);
    }
    return 0;
}