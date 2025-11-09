#include "fat.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char sector_buf[512];
char rde_region[16384];
int fd = 0;

int read_sector_from_disk_image(unsigned int sector_num, char *buf, unsigned int nsectors) {
    lseek(fd, sector_num * 512, SEEK_SET);
    int n = read(fd, buf, 512 * nsectors);
    return n;
}

void extract_filename(struct root_directory_entry *rde, char *fname){
    int k = 0;
    while(((rde->file_name)[k] != ' ') && (k < 8)){
        fname[k] = (rde->file_name)[k];
        k++;
    }
    fname[k] = '\0';
    if((rde->file_extension)[0] == ' ') return;
    fname[k++] = '.';
    fname[k] = '\0';
    int n = 0;
    while(((rde->file_extension)[n] != ' ') && (n < 3)){
        fname[k] = (rde->file_extension)[n];
        k++;
        n++;
    }
    fname[k] = '\0';
}

int main() {
    struct boot_sector *bs = (struct boot_sector*)sector_buf;
    struct root_directory_entry *rde_tbl = (struct root_directory_entry*)rde_region;

    fd = open("rootfs.img", O_RDONLY);
    if(fd < 0){
        perror("Failed to open rootfs.img");
        return 1;
    }

    read_sector_from_disk_image(0, sector_buf, 1);

    printf("sectors per cluster = %d\n", bs->num_sectors_per_cluster);
    printf("reserved sectors = %d\n", bs->num_reserved_sectors);
    printf("num fat tables = %d\n", bs->num_fat_tables);
    printf("num RDEs = %d\n", bs->num_root_dir_entries);

    read_sector_from_disk_image(bs->num_reserved_sectors + bs->num_fat_tables * bs->num_sectors_per_fat,
                                rde_region, 32);

    for(int k = 0; k < 512; k++) {
        char temp_str[16];
        extract_filename(&rde_tbl[k], temp_str);
        if(temp_str[0] != '\0') {
            printf("fname = %s\n", temp_str);
        }
    }

    close(fd);
    return 0;
}
