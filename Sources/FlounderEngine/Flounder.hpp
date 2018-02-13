#pragma once

//
// Flounder header file
//

#include "Camera/Camera.hpp"
#include "Camera/ICamera.hpp"
#include "Camera/IPlayer.hpp"
#include "Deferred/RendererDeferred.hpp"
#include "Deferred/UbosDeferred.hpp"
#include "Devices/Audio.hpp"
#include "Devices/Display.hpp"
#include "Devices/Joysticks.hpp"
#include "Devices/Keyboard.hpp"
#include "Devices/Mouse.hpp"
#include "Engine/Engine.hpp"
#include "Engine/IModule.hpp"
#include "Engine/IUpdater.hpp"
#include "Entities/Components/ComponentCollider.hpp"
#include "Entities/Components/ComponentCollision.hpp"
#include "Entities/Components/ComponentLight.hpp"
#include "Entities/Components/ComponentMaterial.hpp"
#include "Entities/Components/ComponentModel.hpp"
#include "Entities/Components/ComponentCelestial.hpp"
#include "Entities/Components/ComponentSway.hpp"
#include "Entities/Prefabs/ComponentPrefab.hpp"
#include "Entities/Prefabs/EntityPrefab.hpp"
#include "Entities/Prefabs/Components.hpp"
#include "Entities/Entities.hpp"
#include "Entities/Entity.hpp"
#include "Entities/EntityRender.hpp"
#include "Entities/IComponent.hpp"
#include "Entities/RendererEntities.hpp"
#include "Entities/UbosEntities.hpp"
#include "Events/EventChange.hpp"
#include "Events/Events.hpp"
#include "Events/EventStandard.hpp"
#include "Events/EventTime.hpp"
#include "Events/IEvent.hpp"
#include "Files/Config.hpp"
#include "Files/ConfigKey.hpp"
#include "Files/Csv/FileCsv.hpp"
#include "Files/IFile.hpp"
#include "Files/Xml/FileXml.hpp"
#include "Files/Xml/XmlNode.hpp"
#include "Fonts/Character.hpp"
#include "Fonts/FontFamily.hpp"
#include "Fonts/FontType.hpp"
#include "Fonts/Justify.hpp"
#include "Fonts/Line.hpp"
#include "Fonts/Metafile.hpp"
#include "Fonts/RendererFonts.hpp"
#include "Fonts/Text.hpp"
#include "Fonts/UbosFonts.hpp"
#include "Fonts/Word.hpp"
#include "Guis/Gui.hpp"
#include "Guis/RendererGuis.hpp"
#include "Guis/UbosGuis.hpp"
#include "Helpers/FileSystem.hpp"
#include "Helpers/FormatString.hpp"
#include "Helpers/SquareArray.hpp"
#include "Inputs/AxisButton.hpp"
#include "Inputs/AxisCompound.hpp"
#include "Inputs/AxisJoystick.hpp"
#include "Inputs/ButtonCompound.hpp"
#include "Inputs/ButtonJoystick.hpp"
#include "Inputs/ButtonKeyboard.hpp"
#include "Inputs/ButtonMouse.hpp"
#include "Inputs/IAxis.hpp"
#include "Inputs/IButton.hpp"
#include "Lights/Fog.hpp"
#include "Lights/Light.hpp"
#include "Resources/IResource.hpp"
#include "Resources/Resources.hpp"
#include "Maths/Colour.hpp"
#include "Maths/Delta.hpp"
#include "Maths/Maths.hpp"
#include "Maths/Matrix2.hpp"
#include "Maths/Matrix3.hpp"
#include "Maths/Matrix4.hpp"
#include "Maths/Quaternion.hpp"
#include "Maths/Timer.hpp"
#include "Maths/Transform.hpp"
#include "Maths/Vector2.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Vector4.hpp"
#include "Models/Model.hpp"
#include "Models/Shapes/ShapeCube.hpp"
#include "Models/Shapes/MeshPattern.hpp"
#include "Models/Shapes/MeshSimple.hpp"
#include "Models/Shapes/Rectangle.hpp"
#include "Models/Shapes/ShapeSphere.hpp"
#include "Models/Vertex.hpp"
#include "Models/VertexData.hpp"
#include "Noise/NoiseFast.hpp"
#include "Particles/Particle.hpp"
#include "Particles/Particles.hpp"
#include "Particles/ParticleSystem.hpp"
#include "Particles/ParticleType.hpp"
#include "Particles/RendererParticles.hpp"
#include "Particles/Spawns/ISpawnParticle.hpp"
#include "Particles/Spawns/SpawnCircle.hpp"
#include "Particles/Spawns/SpawnLine.hpp"
#include "Particles/Spawns/SpawnPoint.hpp"
#include "Particles/Spawns/SpawnSphere.hpp"
#include "Physics/Aabb.hpp"
#include "Physics/Frustum.hpp"
#include "Physics/ICollider.hpp"
#include "Physics/Intersect.hpp"
#include "Physics/Ray.hpp"
#include "Physics/Sphere.hpp"
#include "Post/Filters/FilterCrt.hpp"
#include "Post/Filters/FilterDefault.hpp"
#include "Post/Filters/FilterEmboss.hpp"
#include "Post/Filters/FilterFxaa.hpp"
#include "Post/Filters/FilterGrain.hpp"
#include "Post/Filters/FilterGrey.hpp"
#include "Post/Filters/FilterLensflare.hpp"
#include "Post/Filters/FilterNegative.hpp"
#include "Post/Filters/FilterPixel.hpp"
#include "Post/Filters/FilterSepia.hpp"
#include "Post/Filters/FilterTiltshift.hpp"
#include "Post/Filters/FilterTone.hpp"
#include "Post/Filters/FilterWobble.hpp"
#include "Post/IPostFilter.hpp"
#include "Post/IPostPipeline.hpp"
#include "Renderer/Buffers/Buffer.hpp"
#include "Renderer/Buffers/IndexBuffer.hpp"
#include "Renderer/Buffers/UniformBuffer.hpp"
#include "Renderer/Buffers/VertexBuffer.hpp"
#include "Renderer/IManagerRender.hpp"
#include "Renderer/IRenderer.hpp"
#include "Renderer/Pass/RenderPass.hpp"
#include "Renderer/Pipelines/Pipeline.hpp"
#include "Renderer/Pipelines/PipelineCreate.hpp"
#include "Renderer/Queue/QueueFamily.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Stencils/DepthStencil.hpp"
#include "Renderer/Swapchain/Framebuffers.hpp"
#include "Renderer/Swapchain/Swapchain.hpp"
#include "Shadows/RendererShadows.hpp"
#include "Shadows/ShadowBox.hpp"
#include "Shadows/Shadows.hpp"
#include "Shadows/UbosShadows.hpp"
#include "Skyboxes/RendererSkyboxes.hpp"
#include "Skyboxes/Skybox.hpp"
#include "Skyboxes/Skyboxes.hpp"
#include "Skyboxes/UbosSkyboxes.hpp"
#include "Sounds/Sound.hpp"
#include "Sounds/SoundBuffer.hpp"
#include "Space/ISpatialObject.hpp"
#include "Space/ISpatialStructure.hpp"
#include "Space/StructureBasic.hpp"
#include "Standards/IStandard.hpp"
#include "Standards/Standards.hpp"
#include "Tasks/Tasks.hpp"
#include "Terrains/MeshTerrain.hpp"
#include "Terrains/RendererTerrains.hpp"
#include "Terrains/Terrain.hpp"
#include "Terrains/Terrains.hpp"
#include "Terrains/UbosTerrains.hpp"
#include "Textures/Cubemap.hpp"
#include "Textures/Texture.hpp"
#include "Uis/IManagerUis.hpp"
#include "Uis/InputButton.hpp"
#include "Uis/InputDelay.hpp"
#include "Uis/InputGrabber.hpp"
#include "Uis/InputSlider.hpp"
#include "Uis/InputText.hpp"
#include "Uis/UiBound.hpp"
#include "Uis/UiObject.hpp"
#include "Uis/Uis.hpp"
#include "Uis/UiSelector.hpp"
#include "Uis/UiStartLogo.hpp"
#include "Visual/DriverBounce.hpp"
#include "Visual/DriverConstant.hpp"
#include "Visual/DriverFade.hpp"
#include "Visual/DriverLinear.hpp"
#include "Visual/DriverSinwave.hpp"
#include "Visual/DriverSlide.hpp"
#include "Visual/IDriver.hpp"
#include "Visual/Interpolation/SmoothFloat.hpp"
#include "Waters/MeshWater.hpp"
#include "Waters/RendererWaters.hpp"
#include "Waters/UbosWaters.hpp"
#include "Waters/Water.hpp"
#include "Waters/Waters.hpp"
#include "Worlds/Worlds.hpp"
