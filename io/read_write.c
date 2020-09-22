static ssize_t write_to_client(int client_fd, const char *msg, size_t msize)
{
    size_t accum_msize = 0;
    ssize_t write_msize;

    if (msg == NULL || msize <= 0) {
        errno = EINVAL;
        return -1;
    }

    do {

        write_msize = write(client_fd, msg-accum_msize, msize-accum_msize);

        if (write_msize < 0) {          /* error, check errno */
            if (errno == EINTR) {
//                DBGP("interrupted.. restart write.\n");
                continue;
            } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
//                DBGP("client not ready, try again later.\n");
                break;
            }
        } else if (write_msize == 0) {  /* EOF: disconnected */
//            DBGP("write size: 0, try again later.\n");
            close(client_fd);
            break;
        } else if (write_msize > 0) {   /* written */
            accum_msize += write_msize;
//            DBGP("write size: %d  total: %d\n", write_msize, accum_msize);
            if (accum_msize == msize)
                break;
        } else {
            perror("write()");
            return -1;
        }

    } while (write_msize > 0);

    return accum_msize;
}

static ssize_t read_from_client(int client_fd, char *buff, size_t msize)
{
    size_t accum_msize = 0;
    ssize_t read_msize;

    if (buff == NULL || msize <= 0) {
        errno = EINVAL;
        return -1;
    }

    do {

        read_msize = read(client_fd, buff+accum_msize, msize-accum_msize);

        if (read_msize < 0) {          /* error, check errno */
            if (errno == EINTR) {
//                DBGP("interrupted.. restart read.\n");
                continue;
            } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
//                DBGP("client not ready, try again later.\n");
                break;
            }
        } else if (read_msize == 0) {  /* EOF: disconnected */
//            DBGP("read size: 0, try again later.\n");
            close(client_fd);
            break;
        } else if (read_msize > 0) {   /* read */
            accum_msize += read_msize;
//            DBGP("read size: %d  total: %d\n", read_msize, accum_msize);
            if (accum_msize > msize) {
//                DBGP("buff full.\n");
                break;
            } else if (accum_msize < msize) {
//                DBGP("end of read.\n");
                break;
            }
        } else {
            perror("read()");
            return -1;
        }

    } while (read_msize > 0);

    return accum_msize;
}
