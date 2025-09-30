#pragma warning(push, 0)
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#pragma(pop)

#pragma warning(disable :5045)

typedef struct
{
  uint32_t x;
  uint32_t y;
} start_coord_t;

// void ft_printf(uint32_t grid_dim)
// {
//   OutputDebugStringA("===print===\n");
//   char buf[64];
//   // snprintf(buf, sizeof(buf), "%d\n", 10);
//   snprintf(buf, sizeof(buf), "%u\n", grid_dim);
//   OutputDebugStringA(buf);
// }

uint8_t *res = NULL;
uint32_t next_grid[2048][2048] = {0};
int iteration = 0;
uint8_t *res1 = NULL;

uint8_t *simulate_life(uint32_t grid_dim, start_coord_t *initial_points, uint32_t initial_point_count)
{
  // if (iteration == 35) {
  //   __debugbreak();
  // }
  // if (grid_dim != 16) {
  //   return NULL;
  // }

  uint32_t grid[16][16] = {0};

  if (res1 == NULL) {
    res1 = (uint8_t *)malloc(grid_dim * grid_dim);
    if (res1 == NULL) return NULL;

    for (int i = 0; i < (grid_dim * grid_dim); ++i) {
      res1[i] = 0;
    }
  }
  else {
    for (uint32_t i = 0; i < grid_dim; ++i) {
      for (uint32_t j = 0; j < grid_dim; ++j) {
        // grid[i][j] = next_grid[i][j];
        res1[i * grid_dim + j] = next_grid[i][j];
      }
    }
  }

  // if (!res) {
  //   for (uint32_t i = 0; i < initial_point_count; ++i) {
  //     uint32_t x = initial_points[i].x;
  //     uint32_t y = initial_points[i].y;
  //     if (x < 16 && y < 16) {
  //       grid[y][x] = 1;
  //     }
  //   }
  // } else {
  //   for (uint32_t i = 0; i < 16; ++i) {
  //     for (uint32_t j = 0; j < 16; ++j) {
  //       grid[i][j] = next_grid[i][j];
  //     }
  //   }
  // }

  if (iteration == 0) {
    for (uint32_t i = 0; i < initial_point_count; ++i) {
      uint32_t x = initial_points[i].x;
      uint32_t y = initial_points[i].y;
      // if (x < 16 && y < 16) {
      //   grid[y][x] = 1;
      // }
      if (x < grid_dim && y < grid_dim) {
        res1[y * grid_dim + x] = 1;
      }
    }
  }

  // uint32_t next_grid[16][16] = {0};

  // uint32_t nbs[16][16] = {0};

  for (uint32_t y = 0; y < grid_dim; ++y) {
      for (uint32_t x = 0; x < grid_dim; ++x) {
      int live_neighbors = 0;

      for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
          if (dx == 0 && dy == 0) continue;

          int nx = x + dx;
          int ny = y + dy;

          if (nx < 0)
              nx += grid_dim;
          if (ny < 0)
            ny += grid_dim;
          if (nx > (grid_dim - 1))
            nx = nx % grid_dim;
          if (ny > (grid_dim - 1))
            ny = ny % grid_dim;

          if (nx >= 0 && nx < 16 && ny >= 0 && ny < 16) {
            live_neighbors += res1[ny * grid_dim + nx];
          }
        }
      }
      // nbs[y][x] = live_neighbors;

      if (res1[y * grid_dim + x]) {
        next_grid[y][x] = (live_neighbors == 2 || live_neighbors == 3) ? 1 : 0;
      } else {
        next_grid[y][x] = (live_neighbors == 3) ? 1 : 0;
      }
    }
  }

  // if (iteration == 36) {
  //   __debugbreak();
  // }

  // for (uint32_t y = 0; y < 16; ++y) {
  //   for (uint32_t x = 0; x < 16; ++x) {
  //     if (nbs[y][x] > 3 || nbs[y][x] < 2) {
  //       next_grid[y][x] = 0;
  //     }
  //   }
  // }

  // uint8_t *res = (uint8_t *)malloc(grid_dim * grid_dim);
  // if (!res) return NULL;

  // if (res == NULL) {
  //   res = (uint8_t *)malloc(grid_dim * grid_dim);
  //   if (res == NULL) return NULL;
  // }

  // for (uint32_t y = 0; y < 16; ++y) {
  //   for (uint32_t x = 0; x < 16; ++x) {
  //     res[y * 16 + x] = grid[y][x];
  //   }
  // } 

  iteration++;
  return res1;
}

