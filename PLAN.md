# Gama Engine Editor MVP - Development Plan

**Goal:** Build a functional game engine editor with ECS, scene management, and serialization.

**Timeline:** 9 days for MVP

---

## 📋 Progress Overview

- [ ] Phase 1: Core ECS Foundation (Days 1-2)
- [ ] Phase 2: Editor UI (Days 3-7)
- [ ] Phase 3: Persistence (Days 8-9)

---

## Phase 1: Core ECS Foundation (Days 1-2)

### Day 1: Transform Component & Entity System ⏱️ 1 day
**Goal:** Create component system and Transform component

**Tasks:**
- [ ] Create `EngineCore/include/EngineCore/Components/Component.h` (base class)
- [ ] Create `EngineCore/include/EngineCore/Components/Transform.h`
- [ ] Create `EngineCore/include/EngineCore/Components/Tag.h`
- [ ] Implement `EngineCore/src/Components/Transform.cpp`
- [ ] Refactor `Entity.h` to support component template system:
  - [ ] `AddComponent<T>()`
  - [ ] `GetComponent<T>()`
  - [ ] `HasComponent<T>()`
  - [ ] `RemoveComponent<T>()`
- [ ] Update `EngineCore/CMakeLists.txt` to include new component files
- [ ] Test: Create entity, add Transform, modify values

**Files to Create:**
```
EngineCore/include/EngineCore/Components/Component.h
EngineCore/include/EngineCore/Components/Transform.h
EngineCore/include/EngineCore/Components/Tag.h
EngineCore/src/Components/Transform.cpp
```

**Files to Modify:**
```
EngineCore/include/EngineCore/Entity.h
EngineCore/src/Entity.cpp
EngineCore/CMakeLists.txt
```

**Success Criteria:**
- ✅ Can create Entity and add Transform component
- ✅ Can get/modify Transform position, rotation, scale
- ✅ Compiles without errors

---

### Day 2: Scene Class ⏱️ 1 day
**Goal:** Container for managing multiple entities

**Tasks:**
- [ ] Create `EngineCore/include/EngineCore/Scene.h`
- [ ] Implement `EngineCore/src/Scene.cpp`
  - [ ] `CreateEntity(name)` - Returns Entity*
  - [ ] `DestroyEntity(entity)` - Removes from scene
  - [ ] `GetEntityByName(name)` - Find entity
  - [ ] `GetAllEntities()` - Returns vector of entities
  - [ ] `Update(deltaTime)` - Update all entities
  - [ ] `Clear()` - Destroy all entities
- [ ] Integrate Scene into `EditorApp`
  - [ ] Add `Scene* m_ActiveScene` member
  - [ ] Create default scene in Init()
- [ ] Update `EngineCore/CMakeLists.txt`
- [ ] Test: Create multiple entities, iterate through them

**Files to Create:**
```
EngineCore/include/EngineCore/Scene.h
EngineCore/src/Scene.cpp
```

**Files to Modify:**
```
Editor/include/Editor/EditorApp.h
Editor/src/EditorApp.cpp
EngineCore/CMakeLists.txt
```

**Success Criteria:**
- ✅ Can create multiple entities in a scene
- ✅ Can destroy entities
- ✅ Can find entities by name
- ✅ EditorApp has active scene

---

## Phase 2: Editor UI (Days 3-7)

### Day 3: Scene Hierarchy Panel ⏱️ 1 day
**Goal:** Display entity list, implement selection

**Tasks:**
- [ ] Create `Editor/include/Editor/Panels/SceneHierarchyPanel.h`
- [ ] Implement `Editor/src/Panels/SceneHierarchyPanel.cpp`
  - [ ] `OnImGuiRender()` - Draw entity tree with `ImGui::TreeNode`
  - [ ] `SetContext(Scene*)` - Set active scene
  - [ ] Entity selection handling (click to select)
  - [ ] Highlight selected entity
- [ ] Add selection state to EditorApp
  - [ ] Add `Entity* m_SelectedEntity` member
  - [ ] Pass to hierarchy panel
- [ ] Integrate panel into `EditorApp::RenderUI()`
- [ ] Update `Editor/CMakeLists.txt`
- [ ] Test: Create entities, see them in hierarchy, click to select

**Files to Create:**
```
Editor/include/Editor/Panels/SceneHierarchyPanel.h
Editor/src/Panels/SceneHierarchyPanel.cpp
```

**Files to Modify:**
```
Editor/include/Editor/EditorApp.h
Editor/src/EditorApp.cpp
Editor/CMakeLists.txt
```

**Success Criteria:**
- ✅ Hierarchy panel shows all entities in scene
- ✅ Can click entity to select it
- ✅ Selected entity is visually highlighted

---

### Day 4: Scene Hierarchy - Context Menu & Create ⏱️ 1 day
**Goal:** Add/delete entities from hierarchy

**Tasks:**
- [ ] Implement "Create Entity" button/menu item
  - [ ] Add to hierarchy panel header
  - [ ] Create entity with auto-generated name (Entity 0, Entity 1, etc.)
- [ ] Implement right-click context menu
  - [ ] "Delete Entity" option
  - [ ] "Duplicate Entity" option (optional)
- [ ] Add entity name editing
  - [ ] Double-click entity name to rename
  - [ ] Edit Tag component name
- [ ] Visual polish
  - [ ] Icons for entities (optional)
  - [ ] Better highlight color
- [ ] Test: Create 5+ entities, delete some, rename them

**Files to Modify:**
```
Editor/src/Panels/SceneHierarchyPanel.cpp
```

**Success Criteria:**
- ✅ Can create new entities from UI
- ✅ Can delete entities via right-click
- ✅ Can rename entities

---

### Day 5: Inspector Panel - Part 1 ⏱️ 1 day
**Goal:** Display selected entity's components

**Tasks:**
- [ ] Create `Editor/include/Editor/Panels/InspectorPanel.h`
- [ ] Implement `Editor/src/Panels/InspectorPanel.cpp`
  - [ ] `OnImGuiRender()` - Draw component list
  - [ ] `SetSelectedEntity(Entity*)` - Update selection
  - [ ] Display Tag component
    - [ ] Show entity name (editable text field)
  - [ ] Display Transform component
    - [ ] Position X, Y, Z with `ImGui::DragFloat3`
    - [ ] Rotation X, Y, Z with `ImGui::DragFloat3`
    - [ ] Scale X, Y, Z with `ImGui::DragFloat3`
- [ ] Integrate panel into `EditorApp::RenderUI()`
- [ ] Update `Editor/CMakeLists.txt`
- [ ] Test: Select entity, edit transform values, see changes

**Files to Create:**
```
Editor/include/Editor/Panels/InspectorPanel.h
Editor/src/Panels/InspectorPanel.cpp
```

**Files to Modify:**
```
Editor/src/EditorApp.cpp
Editor/CMakeLists.txt
```

**Success Criteria:**
- ✅ Inspector shows selected entity's components
- ✅ Can edit Transform position, rotation, scale
- ✅ Changes update in real-time

---

### Day 6: Inspector Panel - Part 2 ⏱️ 1 day
**Goal:** Polish inspector, add component management

**Tasks:**
- [ ] Add collapsible headers for each component
  - [ ] Use `ImGui::CollapsingHeader`
  - [ ] Can expand/collapse Transform, Tag
- [ ] Add "Add Component" dropdown button
  - [ ] List available components
  - [ ] Add selected component to entity
- [ ] Add "Remove Component" button per component
  - [ ] Small X button next to component header
  - [ ] Cannot remove Transform (required)
- [ ] Add "Reset Transform" button
  - [ ] Reset to position(0,0,0), rotation(0,0,0), scale(1,1,1)
- [ ] Visual polish
  - [ ] Better spacing, colors
  - [ ] Component icons (optional)
- [ ] Test: Add/remove components, reset transform

**Files to Modify:**
```
Editor/src/Panels/InspectorPanel.cpp
```

**Success Criteria:**
- ✅ Components have collapsible headers
- ✅ Can add/remove components (except Transform)
- ✅ Can reset Transform to defaults

---

### Day 7: Viewport Improvements ⏱️ 1 day
**Goal:** Better 3D view with editor camera

**Tasks:**
- [ ] Convert viewport to ImGui window
  - [ ] Use `ImGui::Begin("Viewport")`
  - [ ] Make it dockable
  - [ ] Render to framebuffer texture
- [ ] Create `Editor/include/Editor/EditorCamera.h`
- [ ] Implement `Editor/src/EditorCamera.cpp`
  - [ ] Camera position, rotation
  - [ ] WASD movement
  - [ ] Mouse look (right-click + drag to rotate)
  - [ ] Scroll wheel zoom (move forward/back)
  - [ ] Smooth movement with deltaTime
- [ ] Integrate EditorCamera into EditorApp
  - [ ] Update camera in `Update()`
  - [ ] Use camera view matrix for rendering
- [ ] Render scene entities in viewport
  - [ ] Use Transform component data
- [ ] Draw grid/axis helpers (optional)
  - [ ] XZ grid plane
  - [ ] RGB XYZ axes
- [ ] Update `Editor/CMakeLists.txt`
- [ ] Test: Move camera with WASD, rotate with mouse, zoom with scroll

**Files to Create:**
```
Editor/include/Editor/EditorCamera.h
Editor/src/EditorCamera.cpp
```

**Files to Modify:**
```
Editor/src/EditorApp.cpp
Editor/CMakeLists.txt
```

**Success Criteria:**
- ✅ Viewport is dockable ImGui window
- ✅ WASD moves camera
- ✅ Right-click + drag rotates camera
- ✅ Scroll wheel zooms
- ✅ Can see entities with transforms in 3D

---

## Phase 3: Persistence (Days 8-9)

### Day 8: Scene Serialization - Save ⏱️ 1 day
**Goal:** Save scenes to JSON files

**Tasks:**
- [ ] Add dependency: `nlohmann-json` to vcpkg
- [ ] Update vcpkg to install nlohmann-json (or use header-only)
- [ ] Implement Component serialization
  - [ ] Add `virtual void Serialize(json& j)` to Component base
  - [ ] Implement in Transform: save position, rotation, scale
  - [ ] Implement in Tag: save name
- [ ] Implement `Scene::SaveToFile(filepath)` in `Scene.cpp`
  - [ ] Serialize all entities
  - [ ] For each entity, serialize all components
  - [ ] Write JSON to file
- [ ] Add "Save Scene" menu item in `EditorApp`
  - [ ] File → Save Scene (Ctrl+S)
  - [ ] Use ImGuiFileDialog or native file dialog
  - [ ] Default to `.scene` extension
- [ ] Test: Create scene with multiple entities, save to `test.scene`, inspect JSON

**JSON Format Example:**
```json
{
  "entities": [
    {
      "name": "Entity 0",
      "components": {
        "Tag": {
          "name": "Entity 0"
        },
        "Transform": {
          "position": [0, 0, 0],
          "rotation": [0, 0, 0],
          "scale": [1, 1, 1]
        }
      }
    }
  ]
}
```

**Files to Modify:**
```
EngineCore/include/EngineCore/Components/Component.h
EngineCore/include/EngineCore/Components/Transform.h
EngineCore/include/EngineCore/Scene.h
EngineCore/src/Components/Transform.cpp
EngineCore/src/Scene.cpp
Editor/src/EditorApp.cpp
```

**Success Criteria:**
- ✅ Can save scene to `.scene` JSON file
- ✅ JSON contains all entities and their components
- ✅ File can be opened and read as valid JSON

---

### Day 9: Scene Serialization - Load & Menu ⏱️ 1 day
**Goal:** Load scenes from JSON, complete file menu

**Tasks:**
- [ ] Implement Component deserialization
  - [ ] Add `virtual void Deserialize(json& j)` to Component base
  - [ ] Implement in Transform: load position, rotation, scale
  - [ ] Implement in Tag: load name
- [ ] Implement `Scene::LoadFromFile(filepath)` in `Scene.cpp`
  - [ ] Clear current scene
  - [ ] Parse JSON file
  - [ ] Create entities from JSON
  - [ ] Restore components with deserialized data
- [ ] Add "Open Scene" menu item
  - [ ] File → Open Scene (Ctrl+O)
  - [ ] File dialog to select `.scene` file
  - [ ] Load scene and replace current
- [ ] Add "New Scene" menu item
  - [ ] File → New Scene (Ctrl+N)
  - [ ] Clear current scene (prompt to save if modified)
  - [ ] Create empty scene
- [ ] Add full menu bar to EditorApp
  ```
  File   Edit   View
   ├─ New Scene (Ctrl+N)
   ├─ Open Scene (Ctrl+O)
   ├─ Save Scene (Ctrl+S)
   ├─ Save Scene As... (Ctrl+Shift+S)
   └─ Exit
  ```
- [ ] Add "unsaved changes" tracking
  - [ ] Mark scene as dirty when entities/components modified
  - [ ] Prompt before closing if unsaved
- [ ] Test full workflow:
  1. Create scene with entities
  2. Save scene
  3. Close editor
  4. Reopen editor
  5. Load scene
  6. Verify all entities/transforms restored

**Files to Modify:**
```
EngineCore/include/EngineCore/Components/Component.h
EngineCore/include/EngineCore/Components/Transform.h
EngineCore/include/EngineCore/Scene.h
EngineCore/src/Scene.cpp
Editor/include/Editor/EditorApp.h
Editor/src/EditorApp.cpp
```

**Success Criteria:**
- ✅ Can load `.scene` files
- ✅ All entities and components restored correctly
- ✅ Full File menu with New/Open/Save
- ✅ Unsaved changes warning works

---

## 🎉 MVP Complete!

### Final Checklist
- [ ] Can create entities in Scene Hierarchy
- [ ] Can select entities (highlighted in hierarchy)
- [ ] Can edit Transform (position/rotation/scale) in Inspector
- [ ] Changes reflected in Viewport in real-time
- [ ] Can move camera with WASD + mouse in Viewport
- [ ] Can save scene to `.scene` JSON file
- [ ] Can load scene from file (entities/transforms fully restored)
- [ ] Menu bar with New/Open/Save Scene

---

## 📦 Post-MVP Features (Future Work)

### Play Mode System
- [ ] Play/Pause/Stop buttons in toolbar
- [ ] Switch between Edit mode and Play mode
- [ ] Save scene state before playing
- [ ] Restore scene state on stop

### Additional Components
- [ ] MeshRenderer component (3D model rendering)
- [ ] Camera component (in-game camera)
- [ ] Light component (point/directional/spot lights)
- [ ] Rigidbody component (physics)
- [ ] Script component (Lua behavior)

### Editor Features
- [ ] Gizmos (visual move/rotate/scale handles)
- [ ] Asset browser panel
- [ ] Prefab system
- [ ] Undo/Redo system
- [ ] Multi-selection
- [ ] Copy/Paste entities
- [ ] Scene view camera presets (Top, Front, Side)

### Rendering Improvements
- [ ] PBR materials
- [ ] Shadow mapping
- [ ] Post-processing effects
- [ ] Skybox

### Scripting
- [ ] Lua script hot-reloading
- [ ] Script template generation
- [ ] Script editor integration

---

## 📝 Notes

### Architecture Decisions
- **ECS in EngineCore:** Shared between Editor and Runtime
- **Panels in Editor:** UI-specific, not in EngineCore
- **JSON serialization:** Human-readable, easy to debug
- **ImGui:** Fast iteration, dockable windows

### Dependencies
- GLFW (windowing)
- GLEW (OpenGL)
- ImGui (UI)
- GLM (math - add if needed)
- Lua (scripting)
- Sol2 (Lua binding)
- nlohmann-json (serialization)

### File Structure
```
gama-engine/
├── EngineCore/          # Shared engine library
│   ├── include/
│   │   └── EngineCore/
│   │       ├── Components/
│   │       ├── Entity.h
│   │       ├── Scene.h
│   │       ├── Window.h
│   │       └── Renderer.h
│   └── src/
├── Editor/              # Editor executable
│   ├── include/
│   │   └── Editor/
│   │       ├── Panels/
│   │       └── EditorApp.h
│   └── src/
├── Runtime/             # Game runtime (future)
├── external/            # Header-only dependencies
├── vcpkg.json           # Dependency manifest
└── PLAN.md              # This file!
```

---

**Last Updated:** December 23, 2025  
**Status:** Phase 1 - Not Started  
**Next Step:** Day 1 - Transform Component & Entity System
