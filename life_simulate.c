#pragma warning(push, 0)
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#pragma(pop)

#pragma warning(disable : 5045)

typedef struct {
  uint32_t x;
  uint32_t y;
} start_coord_t;

static uint8_t *grids = NULL;
static uint32_t itr = 0;

uint8_t *simulate_life(uint32_t grid_dim, start_coord_t *init_points,
                       uint32_t init_point_count) {
  if (grids == NULL) {
    grids = (uint8_t *)calloc(2 * grid_dim, sizeof(uint8_t));
    if (!grids)
      return NULL;

    for (uint32_t i = 0; i < init_point_count; i++) {
      uint32_t x = init_points[i].x;
      uint32_t y = init_points[i].y;
      if (x < grid_dim && y < grid_dim) {
        grids[init_points[i].y * grid_dim + init_points[i].x] = 1;
      }
    }
  }

  uint8_t *cur = grids + (itr % 2) * grid_dim * grid_dim;
  uint8_t *nxt = grids + ((itr + 1) % 2) * grid_dim * grid_dim;

  // calc next gen
  for (uint32_t y = 0; y < grid_dim; y++) {
    for (uint32_t x = 0; x < grid_dim; x++) {
      int live_nbs = 0;

      for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
          if (dx == 0 && dy == 0)
            continue;

          uint32_t nx = (x + dx) & (grid_dim - 1);
          uint32_t ny = (y + dy) & (grid_dim - 1);

          live_nbs += cur[ny * grid_dim + nx];
        }
      }

      uint8_t alive = cur[y * grid_dim + x];
      nxt[y * grid_dim + x] =
          (alive ? (live_nbs == 2 || live_nbs == 3) : (live_nbs == 3));
    }
  }

  itr++;
  return nxt;
}
