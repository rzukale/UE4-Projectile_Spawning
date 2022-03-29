## Videolink
https://youtu.be/m-s5mf7VZhU

# HMPhrikeV2 Changelog

- Fixed an annoying bug where playing the YT video would cause windows to play an error sound.
- Expanded Phrike Artifact functionality
- OrbSpawning refactor:
  - Optimized Orb spawning to happen once per tick to stabilize framerate drops.
  - OrbSpawner renamed to OrbSpawnerBase:
  - OrbSpawnerBase has shared variables and virtual functions.
  - OrbSpawnerBase has 2 subclasses, OrbSpawnerHand & OrbSpawnerHead that contain their specific variables and overrided functions.
 
 ## Usage
 - Press '1' to trigger OrbSpawnerHead
 - Press '2' to reset player health
 - Press '3' to trigger OrbSpawnerHand
