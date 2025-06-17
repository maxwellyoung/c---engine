# Infernal Ascent — Design Bible
**Version 0.1 – 17 Jun 2025**

> Grace is subtraction. Descent is enlightenment.

---

## TL;DR
Platformer micro‑Metroidvania where you start god‑mode in Paradiso then descend through nine circles of Hell, shedding powers as penance and learning to traverse with less. Tight Celeste‑tier controls, Vlambeer punch, Animal Well ambience.

## Deep Inspiration
- **Vlambeer game feel** — screen shake, hit‑pause, juicy sound fx.
- **Celeste movement precision** — Coyote frames, jump buffer, stick‑to‑wall forgiveness.
- **Spelunky systemic level toys** — emergent interactions, minimal rules ⇒ rich possibility.
- **Animal Well mood** — wordless curiosity, ambient dread.
- **Fez perspective twist** — hidden symbolism, layered puzzles.
- **Thomas Was Alone minimalism** — geometry + narration = emotion.
- **Mario readable physics** — predictable arcs, friction you can feel.
- **Desert Golf zen** — one rule, eternal variation.
- **Dante’s *Commedia*** — descent structure, allegorical weight.
- **Bolaño detective drift** — poetic digressions in item descriptions.

## Design Pillars
1. **Tactile Purity** – Every frame counts; no input lag; 60 fps locked.
2. **Subtractive Progression** – Losing powers ↔ gaining insight; abilities ≈ narrative beats.
3. **One‑Screen Circles** – Each circle is a dense diorama; pan‑only scrolling killed.
4. **Juice ≠ Noise** – Feedback is purposeful; no particle spam unless symbolic.
5. **Esoteric Lore** – Story told via environmental haiku, not NPC exposition.

## Core Loop
\`\`\`
   Discover entrance ⟶ perform traversal puzzle ⟶ relinquish ability ⟶ unlock shortcut up ⟶ choose next circle
\`\`\`

Player hits moment‑to‑moment flow (jump‑dash‑wallslide) until a circle removes a verb, forcing mastery of what’s left.

## Mechanics

### Movement Constants (baseline Paradiso)
\`\`\`lua
MAX_SPEED        = 200
ACCELERATION     = 2500
FRICTION         = 2000
JUMP_VELOCITY    = -475
GRAVITY          = 900
MAX_FALL_SPEED   = 600
SPRINT_MULTI     = 1.6
DASH_SPEED       = 500
\`\`\`
Tweak with fixed‑timestep 1/120 s physics; interpolate render.

### Ability Loss Order
| Circle | Ability Lost | Design Rationale |
| ------ | ------------ | ---------------- |
| Limbo  | Double‑Jump  | Baby‑step challenge |
| Lust   | Dash         | Remove speed high |
| Gluttony | Sprint   | Enforce deliberate pace |
| Greed  | Wall‑Cling   | Verticality strain |
| Anger  | Attack (if any) | Powerlessness |
| Heresy | Coyote Time | Punishes hesitation |
| Violence | Jump Buffer | Raw precision |
| Fraud  | TBD | Deception mechanic |
| Treachery | Jump (!) | Final puzzle w/ environment shifting |

### Enemy / Hazard DNA
Low‑complexity hazards (saws, flame jets) focusing on traversal timing. Combat optional; if present, Vlambeer‑style 1‑2 hit popcorn.

## Level Structure
- Hub = Paradiso balcony, acts as save + ability shrine.
- Nine spokes, each ~1‑3 screens, unlock in any order (Fez star chart).
- Secret "Purgatorio" time‑trial remix unlocked on 100 % relics.

## Aesthetic
- **Pixel grid 32 × 32** base; player sprite 32 × 32 with six‑frame run, three‑frame idle, four‑frame jump.
- Palette: 32‑colour DB32 but shifted per circle (HSV rotate) to telegraph theme.
- Parallax layer per circle, subtle CRT vignette shader optional.
- Text uses bitmap font “Iosevka Term Italic, 8px”.

## Audio
- FM‑synth pads + low‑bit crush percussion (S‑S‑SFX vibe).
- Adaptive layer fades when ability lost (volume duck, reverb wash).
- Poetry snippets whispered on checkpoint (randomised lines from *Commedia* public‑domain translation).

## Technical Stack
| Layer | Choice | Justification |
| ----- | ------ | ------------- |
| Language | C++20 | Raw control, fits uni OS/graphics deep‑dive |
| Window/Input | **SDL3** | Minimal cruft, gamepad hotplug, cross‑platform |
| Renderer | OpenGL 4.6 Core | Matches COMP612, debug tooling sane |
| Maths | GLM | Header‑only, aligns with others |
| ECS | **EnTT** or custom struct‑of‑arrays | Keep simple; resist YA‑ECS rabbit hole |
| Audio | `miniaudio` | One‑header, easy streaming |
| Build | CMake + Ninja | IDE‑agnostic, VSCode/Clion friendly |
| Toolkit | ImGui debug overlay | Real‑time tweak constants |

### Directory Skeleton
\`\`\`
engine/
  core/ (memory, logging, time)
  gfx/  (renderer, shaders, texture atlas)
  input/
  ecs/
  game/ (states, levels, entities)
  data/ (tilemaps, sprites, audio)
tools/
  atlas_packer/
  level_editor/
\`\`\`

## Development Roadmap
| Milestone | Target | Date (aspirational) |
| --------- | ------ | ------------------- |
| M0 | Engine boot: window, input, texture blit, fixed timestep | 30 Jun 25 |
| M1 | Greybox Paradiso demo (no art) | 15 Jul 25 |
| M2 | Vertical slice (Circle of Limbo complete) | 31 Aug 25 |
| M3 | All circles greyboxed, core loop stable | 30 Nov 25 |
| Beta | Art + audio pass, performance polish | 31 Jan 26 |
| Launch | Itchio + Steam demo | Q2 26 |

## Marketing / Release
- Devlog in public (Mastodon + X @internetmaxwell) every Friday; GIF >  words.
- Pricepoint NZ$15 early‑access, raise to NZ$22 on v1.0.
- Leverage Maxwell music for trailer + OST Bandcamp bundle.

## Risk Register
- **Scope creep** — ruthlessly cut combat features if they delay feel polish.
- **Engine yak‑shave** — 80 / 20 rule: ship game, not engine.
- **Solo fatigue** — schedule “Zero‑dev Sundays”.

## Stretch Goals
- Speedrun timer + in‑game leaderboards via Supabase.
- Shader‑based parallax “dot‑delay” echo (tie‑in with future plugin).
- Level editor release post‑launch for community mods.

---

### Reading / Watching List
- J. Blow: *Game Feel* 2013 talk
- Bennett Foddy: *Input and Framerate* GDC 2020
- Seiji Amasawa: *Celeste 30‑fps Physics at 60‑fps* blog
- *Architecture of Animal Well* – Shared Memory 2024

---

**Remember:** polish the first 10 seconds of controller input; the rest follows.

— Maxwell Young, 17 Jun 2025
